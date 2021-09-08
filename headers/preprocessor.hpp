#pragma once

class PreProcessor
{
    std::ifstream file;
    std::stringstream code;
    std::unordered_set<std::string> imported;

    void process(std::string);
    void import(std::string);
    expr_t make_number();
    expr_t make_identifier();
    oper_t make_operator();
    bool is_operator(char);
    bool is_identifier(char);
    bool is_valid_number_char(char);
    bool is_operator(char);
    
    public:
    std::stringstream& operator()(std::string);
};
