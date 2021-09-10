#pragma once

#include <unordered_set>
#include <fstream>
#include <string>
#include <sstream>

class PreProcessor
{
    std::ifstream file;
    std::stringstream code;
    std::unordered_set<std::string> imported;

    void process(std::string);

    void import();
    void define();

    public:
    PreProcessor() = default;
    std::stringstream& operator()(std::string);
};
