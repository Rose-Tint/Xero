#ifndef SCOPE_HPP
#define SCOPE_HPP

#include <map>
#include <string>

#include "token.hpp"


typedef char level_t;


class Scope
{
    struct ValueHolder
    {
        friend class Scope;
        std::string value;
        std::string& operator=(const std::string& val) { return value = val; }
        ValueHolder(std::string str, level_t lvl) : value(str), level(lvl) {  }
        ValueHolder() : value(""), level(0) {  }
        operator std::string&() { return value; }

        private:
        level_t level;
    };

    level_t level;
    std::map<std::string, ValueHolder> names;

    public:
    Scope() = default;
    void add(std::string id, std::string value);
    void operator++(int) { level++; }
    void operator--(int);
    std::string& operator[](const std::string& key) { return names[key]; }
};

#endif