#ifndef ERRORS_HPP
#define ERRORS_HPP


#include <stdexcept>

namespace err
{
    using std::runtime_error;
    template<int> class _Error_ : public runtime_error
    {
        using runtime_error::runtime_error;
    };

    typedef _Error_<1> ParserError;
    typedef _Error_<2> LexerError;
    typedef _Error_<3> SyntaxError;
    typedef _Error_<4> PreProcessorError;
}

#endif