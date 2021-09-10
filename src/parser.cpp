#include "lexer.hpp"
#include "parser.hpp"


Parser::Parser(std::stringstream input) : lxr(input)
{
    ;
}


void Parser::operator<<(expr_t node)
{
    // head is the expr that is already a part of the tree
    if (head.token.is_final()) return; // base case
    else switch (node.token.type)
    {
        case (BIOP):
        {
            if (left == nullptr) *left = expr;
            else if (left->is_final()) (right == nullptr) ? *right = expr : right->add(expr, scp);
            else left->add(expr, scp);
        } break;

        case (UNOP):
        {
            if (left == nullptr) *left = expr; else left->add(expr, scp);
        } break;

        case (KEYWORD):
        {
            ;
        } break;

        case (IDENTIFIER)

        default: throw -2;
    }

    // NOT FINISHED
}


expr_t Parser::operator()()
{
    token_t token = lxr.next_token();
    ast = expr_t(token);
    while (lxr.next_token(token))
    {
        ast.add(token);
    }
    return root;
}

