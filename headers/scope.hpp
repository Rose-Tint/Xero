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

        private:
        level_t level;
    };

    level_t level = 0;
    std::map<std::string, ValueHolder> names;

    public:
    Scope() = default;
    void add(std::string id, std::string value) { names.insert(id, { value, level }); }
    void operator++(int) { level++; }
    void operator--(int);
    ValueHolder& operator[](const std::string& key) { return names[key]; }
};

#endif