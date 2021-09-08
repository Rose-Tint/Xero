#pragma once

#include "expression.hpp"


struct AbstractSyntaxTree
{
    expr_t expr;
    AbstractSyntaxTree* left = null_ptr;
    AbstractSyntaxTree* right = null_ptr;
};


typedef AbstractSyntaxTree ast_t, *ast_ptr_t;
