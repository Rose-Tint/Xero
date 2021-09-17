#include "parser.hpp"
#include "error.hpp"


ExprPtr Parser::scope()
{
    ExprPtr expr(LBRACE);
    scp++;
    while (lxr.get() != RBRACE) expr.add(assign());
    scp--;
    root.add(expr);
    return expr;
}


ExprPtr Parser::assign()
{
    Token tok = lxr.get();
    ExprPtr expr = add();
    if (lxr.get() == ASN)
    {
        expr.add(ExprPtr(ASN));
        if (tok != ID) throw err::ParserError("left side of assignment must be an identifier");
        std::string id = lxr.get_val();
        expr.add(ExprPtr(ID, id));
        lxr.next();
        expr.add(add());
        scp.add(id, lxr.get_val());
    }
    return expr;
}


ExprPtr Parser::add()
{
    ExprPtr expr = mul();
    while (1)
    {
        Token token = lxr.get();
        switch (token)
        {
            case (PLUS): // intentional fallthrough
            case (MINUS):
                expr.add(ExprPtr(token));
                lxr.next();
                expr.add(mul());
                break;
            default:
                return expr;
        }
    }
}


ExprPtr Parser::mul()
{
    ExprPtr expr = cmp();
    while (1)
    {
        Token token = lxr.get();
        switch (token)
        {
            case (MUL):
            case (DIV):
            case (MOD):
                expr.add(ExprPtr(token));
                lxr.next();
                expr.add(cmp());
                break;
            default:
                return expr;
        }
    }
}


ExprPtr Parser::cmp()
{
    ExprPtr expr = eq();
    while (1)
    {
        Token token = lxr.get();
        switch (token)
        {
            case (LT):
            case (GT):
                expr.add(ExprPtr(token));
                lxr.next();
                expr.add(eq());
                break;
            default:
                return expr;
        }
    }
}


ExprPtr Parser::eq()
{
    ExprPtr expr = _xor();
    while (1)
    {
        Token token = lxr.get();
        if (token == EQ)
        {
            expr.add(ExprPtr(token));
            lxr.next();
            expr.add(_xor());
        }
        else return expr;
    }
}


ExprPtr Parser::_xor()
{
    ExprPtr expr = _or();
    while (1)
    {
        Token token = lxr.get();
        if (token == XOR)
        {
            expr.add(ExprPtr(token));
            lxr.next();
            expr.add(_or());
        }
        else return expr;
    }
}


ExprPtr Parser::_or()
{
    ExprPtr expr = _and();
    while (1)
    {
        Token token = lxr.get();
        if (token == OR)
        {
            expr.add(ExprPtr(token));
            lxr.next();
            expr.add(_and());
        }
        else return expr;
    }
}


ExprPtr Parser::_and()
{
    ExprPtr expr = unary();
    while (1)
    {
        Token token = lxr.get();
        if (token == AND)
        {
            expr.add(ExprPtr(token));
            lxr.next();
            expr.add(unary());
        }
        else return expr;
    }
}


ExprPtr Parser::unary()
{
    ExprPtr expr = terminal();
    while (1)
    {
        Token token = lxr.get();
        switch (token)
        {
            case (PLUS):
            case (MINUS):
            case (NOT):{
                ExprPtr unary = _Expr_::unary(token);
                lxr.next();
                unary.add(terminal());
                expr.add(unary);
            } break;
            default:
                return expr;
        }
    }
}


ExprPtr Parser::terminal()
{
    static int expr_c = 0;
    std::string arg_s = lxr.get_val();
    ExprPtr expr;
    Token token = lxr.get();
    lxr.next();
    switch (token)
    {
        case ID:
            expr = ExprPtr(token, scp[arg_s]);
            break;
        case NUM:
            expr = ExprPtr(token, arg_s);
            break;
        case LPAREN:
            expr = add();
            if (token != RPAREN) throw err::ParserError("expected ')'");
            break;
        case LBRACE:
            expr = scope();
            if (lxr.get() != RBRACE) throw err::ParserError("expected '}'");
            break;
        case ENDL:
            expr = assign();
            break;
        default:
            throw err::ParserError("expression '" + expr.value() + "' fell through to terminal but is invalid terminal expression");
    }
    return expr;
}


ExprPtr Parser::operator()()
{
    lxr.next();
    root.add(scope());
    return root;
}
