#ifndef PREPROCESSOR_HPP
#define PREPROCESSOR_HPP

#include <unordered_set>
#include <fstream>
#include <string>
#include <sstream>

class PreProcessor
{
    typedef std::unordered_set<std::string> str_set;

    std::ifstream curr_file;
    std::stringstream code;
    str_set imported;
    str_set defined;

    // utils
    void check_and_recurse(str_set&, std::string) = delete;
    void ignore_until(char c) { while (curr_file.get() != c); }
    std::string get_until(char);
    std::string get_between(char, char);

    void process(std::string);

    // directives
    void direct();
    void import();
    void define();
    void ifdef();
    void ifnotdef();
    void then(); // not a directive, but called by ifdef and ifnotdef

    public:
    PreProcessor() = default;
    std::stringstream operator()(std::string);
};

#endif