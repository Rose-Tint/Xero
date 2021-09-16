#include "expression.hpp"
#include "error.hpp"


bool Expr::entrance_made = false;


std::ostream& operator<<(std::ostream& out, Expr& expr)
{
    // unsigned int depth = expr.depth();
    // for (unsigned int i = 0; i < depth; i++) out << "\n";
    // for (unsigned int i = 0; i < depth; i++) out << "   ";
    out << expr.value;
    if (expr.left != nullptr) out << *expr.left;
    if (expr.right != nullptr) out << *expr.right;
    return out;
}


unsigned int Expr::depth() const
{
    if (left == nullptr)
    {
        if (right == nullptr) return 1;
        return right->depth();
    }
    else if (right == nullptr) return left->depth();
    else return std::max(left->depth(), right->depth());
}


Expr::Expr(Token tok)
    : token(tok)
{
    switch (token) // any fallthrough is intentional for matching
    {
        case NUM:
        case ID:
            throw err::SyntaxError(std::string("identifier with no identifier found somehow"));
        case EXIT:
            value = "__EXIT__";
            break;
        case ENTRY:
            if (entrance_made) throw err::SyntaxError(std::string("application entry can only be made once"));
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


Expr::Expr(Token tok, std::string val)
    : token(tok), value(val)
{
    std::cout << value;;
}


Expr::Expr(Token tok, char c)
    : token(tok), value(1, c)
{
    std::cout << value;;
}


void Expr::mov(Expr&& other)
{
    left = other.left;
    right = other.left;
    token = other.token;
    value = other.value;
    other.left = nullptr;
    other.right = nullptr;
    other.value = "";
}


void Expr::cpy(const Expr& other)
{
    delete left;
    delete right;
    token = other.token;
    value = other.value;
    left = other.left;
    right = other.right;
}


Expr& Expr::operator=(Expr&& other)
{
    if (this == &other) return *this;
    if (token == ENTRY) throw err::SyntaxError(std::string("entry cannot be moved"));
    mov(std::move(other));
    return *this;
}


Expr& Expr::operator=(const Expr& other)
{
    if (this == &other) return *this;
    cpy(other);
    return *this;
}


Expr* Expr::unary(Token token)
{
    Expr* expr = new Expr(token);
    expr->right = new Expr(EMPTY);
    return expr;
}


void Expr::add(Expr* expr)
{
    if (terminates()) throw err::SyntaxError(std::string("expression terminates, but was told to add an expr"));
    if (left == nullptr) left = expr;
    else if (!left->terminates()) left->add(expr);
    else if (right == nullptr) right = expr;
    else if (!right->terminates() && right->token != EMPTY) right->add(expr);
    else throw err::SyntaxError(std::string("reached end of Expr::add"));
}


bool Expr::terminates() const
{
    if (token == ID || token == NUM) return true;
    if (left == nullptr || right == nullptr) return false;
    else return (left->terminates() && right->terminates());
}
