#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <stdexcept>


namespace err
{
    using std::runtime_error;
    struct Error : public runtime_error
    {
        using runtime_error::runtime_error;
    };

    struct ExprError : Error { using Error::Error; };
    struct UnaddableExprError : ExprError { using ExprError::ExprError; };
    struct ParserError : Error { using Error::Error; };
    struct LexerError : Error { using Error::Error; };
    struct SyntaxError : Error { using Error::Error; };
    struct PreProcessorError : Error { using Error::Error; };
}

#endif