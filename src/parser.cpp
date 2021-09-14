#include "parser.hpp"


Parser::Parser(std::stringstream& input_code)
    : lxr(input_code)
{
    *root = BlockExpr(&top_lvl_token_ref);
    scp = Scope();
}


// TOKEN
// IDENTIFIER
// KEYWORD
// SYMBOL
// SEP
// OPERATOR
// BINARY_OP
// UNARY_OP
// LITERAL
// NUMBER
// STR_LIT


Expr* Parser::operator()()
{
    Token* token;
    Expr* expr;
    NonTerminalExpr* lowest_nt;
    while (lxr.next_token(token))
    {
        lowest_nt = root->get_lowest_free();
        switch (token->id())
        {
            case (IDENTIFIER):
                expr = new TerminalExpr(token);
                lowest_nt->add(expr);
                delete expr;
                break;

            case (KEYWORD):
                expr = new TerminalExpr(token);
                lowest_nt->add(expr);
                delete expr;
                break;

            case (BINARY_OP):
                expr = new BinaryExpr(token);
                lowest_nt->add(expr);
                delete expr;
                break;

            case (UNARY_OP):
                expr = new UnaryExpr(token);
                lowest_nt->add(expr);
                delete expr;
                break;

            case (NUMBER):
                expr = new TerminalExpr(token);
                lowest_nt->add(expr);
                delete expr;
                break;

            case (STR_LIT):
                expr = new TerminalExpr(token);
                lowest_nt->add(expr);
                delete expr;
                break;

            case (SYMBOL):
                // TODO
                break;
        }
    }
}
