#pragma once

#include <fstream>
#include <unordered_set>
#include <stack>
#include <string>
#include <sstream>
#include <vector>
#include "ast.hpp"


class Parser
{
    std::stringstream code;
    std::vector<Expression*> custom_ops;
    std::stack<Expression*> operand_stk;
    std::stack<Expression*> operator_stk;

    void add_custom_oper();
    void process(std::string);
    void import(std::string);
    expr_t* parse();
    expr_t make_number();
    expr_t make_identifier();
    oper_t make_operator();
    bool is_operator(char);
    bool is_identifier(char);
    bool is_valid_number_char(char);
    bool is_operator(char);
    
    public:
    Parser() = default;
    expr_t* operator()(std::vector<token_t>);
};
