#pragma once

#include <fstream>
#include <stack>
#include <string>
#include <sstream>
#include <vector>
#include "ast.hpp"


class Parser
{
    std::ifstream file;
    std::stringstream code;
    std::string filename;
    char advance(bool = false);
    void process();
    void import(std::string);
    std::vector<Expr> custom_ops;
    std::stack<Expr> operand_stk;
    std::stack<Expr> operator_stk;
    Expr* parse();
    Expr make_number();
    Expr make_identifier();
    Expr make_operator();
    bool is_operator(char);
    bool is_identifier(char);
    bool is_valid_number_char(char);
    bool is_operator(char);

    public:
    Parser(std::string);
    Parser(std::string, std::vector<std::string>);
    std::vector<std::string> imported;
    std::stringstream& get_code();
};

const std::vector<std::string> pri_ops
{
    "!",
    "@",
    "#",
    "%",
    "^",
    "&",
    "*",
    "(",
    ")",
    "-",
    "+",
    "=",
    "{",
    "}",
    "[",
    "]",
    "|",
    ":",
    ";",
    "\"",
    "<",
    ">",
    ",",
    ".",
    "/",
    "?"
};
