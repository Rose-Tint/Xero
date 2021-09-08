#pragma once

#include <cstddef>


struct Type
{
    const std::size_t size = 0;
};


const Type Void{ 0 };
const Type Float{ 2 };
const Type Double{ 4 };
const Type Byte{ 1 };
const Type Short{ 2 };
const Type Int{ 4 };
const Type Long{ 8 };
const Type Class{ 0 };
const Type Func{ 0 };
