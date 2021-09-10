#pragma once

#include <cstddef>


struct Type
{
    const std::size_t size;
};


struct Var
{
    Type type;
};


constexpr Type Void{ 0 };
constexpr Type Float{ 2 };
constexpr Type Double{ 4 };
constexpr Type Byte{ 1 };
constexpr Type Short{ 2 };
constexpr Type Int{ 4 };
constexpr Type Long{ 8 };
constexpr Type Class{ 0 };
constexpr Type Func{ 0 };
