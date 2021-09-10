#include "lexer.hpp"
#include "parser.hpp"


expr_t parse(std::stringstream input)
{
    Lexer lxr(input);
    token_t token = lxr.next_token();
    expr_t root(token);
    while (lxr.next_token(token))
    {
        root.add(token);
    }
    return root;
}

