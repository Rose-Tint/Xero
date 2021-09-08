#pragma once

#include <cstddef>


struct Type
{
    const std::size_t size = 0;
};


typedef const Type primitive_t;


primitive_t Void{ 0 };
primitive_t Float{ 2 };
primitive_t Double{ 4 };
primitive_t Byte{ 1 };
primitive_t Short{ 2 };
primitive_t Int{ 4 };
primitive_t Long{ 8 };
primitive_t Class{ 0 };
primitive_t Func{ 0 };
