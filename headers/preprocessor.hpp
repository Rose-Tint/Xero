#pragma once

#include <unordered_set>
#include <fstream>
#include <string>
#include <sstream>

class PreProcessor
{
    typedef std::unordered_set<std::string> str_set;

    std::stringstream code;
    str_set imported;
    str_set defined;

    // utils
    void check_and_recurse(str_set&, std::string);
    void ignore_until(std::ifstream&, char);
    std::string get_until(std::ifstream&, char);
    std::string get_between(std::ifstream&, char, char);

    void process(std::string);

    // directives
    void direct(std::ifstream&);
    void import(std::ifstream&);
    void define(std::ifstream&);
    void ifdef(std::ifstream&);
    void ifnotdef(std::ifstream&);
    void then(std::ifstream&); // not a directive, but called by ifdef and ifnotdef

    public:
    PreProcessor() = default;
    std::stringstream& operator()(std::string);
};
