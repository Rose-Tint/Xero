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
        lowest_nt->add(token);
    }
}
