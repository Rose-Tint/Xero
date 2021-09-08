#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "ast.hpp"


class Parser
{
    std::ifstream file;
    std::stringstream code;
    std::string filename;
    ast_t ast;
    char last_c;
    void parse();
    char advance(bool = false);
    void process();
    void import(std::string);

    public:
    Parser(std::string);
    Parser(std::string, std::vector<std::string>);
    std::vector<std::string> imported;
    std::stringstream& get_code();
};
