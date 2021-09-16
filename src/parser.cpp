#include "parser.hpp"
#include "error.hpp"
#include <iostream>


Expr* Parser::scope()
{
    Expr* expr = new Expr(LBRACE);
    root->add(expr);
    scp++;
    while (lxr.get() != RBRACE) expr->add(assign());
    scp--;
    return expr;
}


Expr* Parser::assign()
{
    Token tok = lxr.get();
    Expr* expr = add();
    if (lxr.get() == ASN)
    {
        expr->add(new Expr(ASN));
        if (tok != ID)
        {
            delete expr;
            delete root;
            throw err::ParserError(std::string("left side of assignment must be an identifier"));
        }
        std::string id = lxr.get_val();
        expr->add(new Expr(ID, id));
        lxr.next();
        expr->add(add());
        scp.add(id, lxr.get_val());
    }
    return expr;
}


Expr* Parser::add()
{
    Expr* expr = mul();
    while (1)
    {
        Token token = lxr.get();
        switch (token)
        {
            case (PLUS): // intentional fallthrough
            case (MINUS):
                expr->add(new Expr(token));
                lxr.next();
                expr->add(mul());
                break;
            default:
                return expr;
        }
    }
}


Expr* Parser::mul()
{
    Expr* expr = cmp();
    while (1)
    {
        Token token = lxr.get();
        switch (token)
        {
            case (MUL):
            case (DIV):
            case (MOD):
                expr->add(new Expr(token));
                lxr.next();
                expr->add(cmp());
                break;
            default:
                return expr;
        }
    }
}


Expr* Parser::cmp()
{
    Expr* expr = eq();
    while (1)
    {
        Token token = lxr.get();
        switch (token)
        {
            case (LT):
            case (GT):
                expr->add(new Expr(token));
                lxr.next();
                expr->add(eq());
                break;
            default:
                return expr;
        }
    }
}


Expr* Parser::eq()
{
    Expr* expr = _xor();
    while (1)
    {
        Token token = lxr.get();
        if (token == EQ)
        {
            expr->add(new Expr(token));
            lxr.next();
            expr->add(_xor());
        }
        else return expr;
    }
}


Expr* Parser::_xor()
{
    Expr* expr = _or();
    while (1)
    {
        Token token = lxr.get();
        if (token == XOR)
        {
            expr->add(new Expr(token));
            lxr.next();
            expr->add(_or());
        }
        else return expr;
    }
}


Expr* Parser::_or()
{
    Expr* expr = _and();
    while (1)
    {
        Token token = lxr.get();
        if (token == OR)
        {
            expr->add(new Expr(token));
            lxr.next();
            expr->add(_and());
        }
        else return expr;
    }
}


Expr* Parser::_and()
{
    Expr* expr = unary();
    while (1)
    {
        Token token = lxr.get();
        if (token == AND)
        {
            expr->add(new Expr(token));
            lxr.next();
            expr->add(unary());
        }
        else return expr;
    }
}


Expr* Parser::unary()
{
    Expr* expr = terminal();
    while (1)
    {
        Token token = lxr.get();
        switch (token)
        {
            case (PLUS):
            case (MINUS):
            case (NOT):{
                Expr* unary = Expr::unary(token);
                lxr.next();
                unary->add(terminal());
                expr->add(unary);
            } break;
            default:
                return expr;
        }
    }
}


Expr* Parser::terminal()
{
    static int expr_c = 0;
    std::string arg_s = lxr.get_val();
    Expr* expr = nullptr;
    Token token = lxr.get();
    lxr.next();
    switch (token)
    {
        case ID:
            expr = new Expr(token, scp[arg_s]);
            break;
        case NUM:
            expr = new Expr(token, arg_s);
            break;
        case LPAREN:
            expr = add();
            if (token != RPAREN)
            {
                delete expr;
                delete root;
                throw err::ParserError(std::string("expected ')'"));
            }
            break;
        case LBRACE:
            expr = scope();
            if (lxr.get() != RBRACE)
            {
                delete expr;
                delete root;
                throw err::ParserError(std::string("expected '}'"));
            }
            break;
        case ENDL:
            expr = assign();
            break;
        default:
            std::string msg = std::to_string(expr_c++) + " exprs made) expression '";
            msg += expr->get_value();
            msg.append("' fell through to terminal but is invalid terminal expression");
            delete expr;
            delete root;
            throw err::ParserError(msg);
    }
    return expr;
}


Expr* Parser::operator()()
{
    lxr.next();
    root->add(scope());
    return root;
}
