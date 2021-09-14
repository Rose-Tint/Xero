#include "parser.hpp"


Parser::Parser(std::stringstream& input_code)
    : lxr(input_code)
{
    *root = BlockExpr(&top_lvl_token_ref);
    scp = Scope();
}


Expr* Parser::operator()()
{
    Token* token;
    while (lxr.next_token(token));
}
