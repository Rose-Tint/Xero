#include "expression.hpp"
#include "error.hpp"


void ExprPtr::destroy() noexcept
{
    delete expr;
    expr = nullptr;
}


ExprPtr::ExprPtr() noexcept
    : expr(nullptr)
{
    ;
}


ExprPtr::ExprPtr(const Token& tok) noexcept
    : expr(new _Expr_(tok))
{
    ;
}


ExprPtr::ExprPtr(const Token& tok, std::string str) noexcept
    : expr(new _Expr_(tok, str))
{
    ;
}


ExprPtr::ExprPtr(const Token& tok, char c) noexcept
    : expr(new _Expr_(tok, c))
{
    ;
}


ExprPtr::ExprPtr(const ExprPtr& other) noexcept
{
    destroy();
    expr = (other.expr == nullptr) ? nullptr : new _Expr_(*other.expr);
}


ExprPtr::ExprPtr(ExprPtr&& other) noexcept
{
    expr = other.expr;
    other.expr = nullptr;
}


ExprPtr& ExprPtr::operator=(const ExprPtr& other) noexcept
{
    if (this == &other) return *this;
    destroy();
    expr = (other.expr == nullptr) ? nullptr : new _Expr_(*other.expr);
    return *this;
}


ExprPtr& ExprPtr::operator=(ExprPtr&& other) noexcept
{
    if (this == &other) return *this;
    expr = other.expr;
    other.expr = nullptr;
    return *this;
}


ExprPtr::~ExprPtr()
{
    delete expr;
    expr = nullptr;
}


void ExprPtr::add(const ExprPtr& arg)
{
    if (is_null()) throw err::ExprError("called ExprPtr::add with a nullptr expr");
    if (this == &arg) throw err::ExprError("attempt to add expr to itself");
    expr->add(arg);
}


bool ExprPtr::is_null() const
{
    return (expr == nullptr);
}


bool ExprPtr::terminates() const
{
    if (is_null()) throw err::ExprError("called ExprPtr::terminates with a nullptr expr");
    return expr->terminates();
}


Token ExprPtr::token() const
{
    if (is_null()) throw err::ExprError("called ExprPtr::token with a nullptr expr");
    return expr->token;
}


ExprPtr ExprPtr::left() const
{
    if (is_null()) throw err::ExprError("called ExprPtr::terminates with a nullptr expr");
    return expr->left;
}


ExprPtr ExprPtr::right() const
{
    if (is_null()) throw err::ExprError("called ExprPtr::right with a nullptr expr");
    return expr->right;
}


std::string ExprPtr::value() const
{
    if (is_null()) throw err::ExprError("called ExprPtr::value with a nullptr expr");
    return expr->value;
}


void ExprPtr::set_left(const ExprPtr& arg)
{
    if (is_null()) throw err::ExprError("called ExprPtr::set_left with a nullptr expr");
    expr->left = arg;
}


void ExprPtr::set_right(const ExprPtr& arg)
{
    if (is_null()) throw err::ExprError("called ExprPtr::set_right with a nullptr expr");
    expr->right = arg;
}


void ExprPtr::set_value(const std::string& val)
{
    if (is_null()) throw err::ExprError("called ExprPtr::set_value with a nullptr expr");
    expr->value = val;
}


ExprPtr ExprPtr::unary(const Token& token)
{
    ExprPtr expr(token);
    expr.set_right(ExprPtr(EMPTY));
    return expr;
}


/* %%%%%%%%% cout overload %%%%%%%%% */


std::ostream& operator<<(std::ostream& out, ExprPtr in)
{
    if (!in.is_null())
    {
        out << in.value();
        if (!in.left().is_null()) out << in.left();
        if (!in.right().is_null()) out << in.right();
    }
    return out;
}


/* %%%%%%%%%% _EXPR_ DEFS %%%%%%%%%% */


bool _Expr_::entrance_made = false;


_Expr_::_Expr_(const Token& tok)
    : token(tok)
{
    switch (token) // if an expression is made without a value arg, token must be one of the following
    {
        case NUM:
        case ID:
            throw err::ExprError("identifier or number with no value found somehow");
        case EXIT:
            value = "__EXIT__";
            break;
        case ENTRY:
            if (entrance_made) throw err::ExprError("application entry can only be made once");
            entrance_made = true;
            value = "__ENTRY__";
            break;
        case EMPTY:
            value = "";
            break;
        default:
            value = (char)token;
    }
}


_Expr_::_Expr_(const Token& tok, std::string val)
    : token(tok), value(val)
{
    ;
}


_Expr_::_Expr_(const Token& tok, char c)
    : token(tok), value(1, c)
{
    ;
}


void _Expr_::add(ExprPtr expr)
{
    if (terminates()) throw err::ExprError("expression terminates, but was told to add an expr");
    if (left.is_null()) left = std::move(expr);
    else if (!left.terminates()) left.add(expr);
    else if (right.is_null()) right = std::move(expr);
    else if (!right.terminates() && right.token() != EMPTY) right.add(expr);
    else throw err::ExprError("reached end of _Expr_::add");
}


bool _Expr_::terminates() const
{
    if (is_terminal(token)) return true;
    else if (left.is_null() || right.is_null()) return false;
    else return (left.terminates() && right.terminates());
}


#ifdef X_TESTS
#include <type_traits>
namespace tst
{
    class TestError {};
    bool operator==(const ExprPtr& l, const ExprPtr& r)
    {
        if (&l == &r) return true;
        if (!l.is_null() && !r.is_null()))
        {
            if (l.token() == r.token() && l.value() == r.value())
            {
                return (l.left() == r.left()) && (l.right() == r.right());
            }
        }
        return false;
    }

    template<class G, class E = G>
    bool check(const G& given, const E& exp)
    {
        return given == exp;
    }

    template<class E, class R, class ...A>
    bool throws_e(R (*f)(A...), A ...args)
    {
        try { f(args...) }
        catch (E) { return true; }
        return false;
    }

    template<Token itok, Token ltok, Token rtok>
    bool test_ExprPtr(std::string ival, std::string lval, std::string rval)
    {
        bool pass = false;
        ExprPtr root = (itok == ID || itok == NUM) ? ExprPtr(itok, ival) : ExprPtr(itok);
        ExprPtr left = (ltok == ID || ltok == NUM) ? ExprPtr(ltok, ival) : ExprPtr(ltok);
        ExprPtr right = (rtok == ID || rtok == NUM) ? ExprPtr(rtok, ival) : ExprPtr(rtok);

        root.add(left);
        root.add(right);
        root.add(Expr(ID, "id"));
        root.add(Expr(NUM, "num"));

        // test constructors and assigners in a new scope for less memory usage
        {
            ExprPtr cpy_ctr(root);
            ExprPtr cpy_op = root;
            ExprPtr mov_ctr(ExprPtr(itok, ival));
            ExprPtr mov_op = ExprPtr(itok, ival);

            try
            {
                pass &= check<ExprPtr>(root, cpy_ctr);
                pass &= check<ExprPtr>(root, cpy_op);
                pass &= check<ExprPtr>(root, mov_ctr);
                pass &= check<ExprPtr>(root, mov_op);
            }
            catch(TestError)
            {
                pass = false;
            }
        }
        try
        {
            pass &= check<bool>(root.is_null(), false);
            pass &= check<Token>(root.token(), itok);
            pass &= check<std::string>(root.value(), ival);
            pass &= check<ExprPtr>(root.left(), left);
            pass &= check<ExprPtr>(root.right(), right);
            pass &= check<bool>(root.terminates(), is_terminal(ltok) && is_terminal(rtok));

            // testing invalid inputs and functions
            {
                ExprPtr nullexpr();
                pass &= throws_e<ExprError, void, const ExprPtr&>(nullexpr.add, root);
                pass &= throws_e<ExprError, void, void>(nullexpr.terminates);
                pass &= throws_e<ExprError, Token, void>(nullexpr.token);
                pass &= throws_e<ExprError, ExprPtr, void>(nullexpr.left);
                pass &= throws_e<ExprError, ExprPtr, void>(nullexpr.right);
                pass &= throws_e<ExprError, std::string, void>(nullexpr.value);
            }
        }
        catch (TestError)
        {
            pass = false;
        }

        return pass;
    }
}
#endif
#endif
