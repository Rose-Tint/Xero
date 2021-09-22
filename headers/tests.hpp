#ifndef TESTS_HPP
#include <iostream>

#include "expression.hpp"
#include "error.hpp"

namespace tst
{
    int rng(int = 0, int = 100);

    class TestError { };

    template<class T>
    static bool check(const T& given, const T& exp) { return given == exp; }

    template<class E, class R, class ...A>
    static bool throws_e(R (*f)(A...), A ...args)
    {
        try { f(args...); }
        catch (E) { return true; }
        return false;
    }

    enum exp_behavior { THROW, EQUATE };

    class ExprPtrTest final
    {
        ExprPtr ref;

        template<exp_behavior, class = err::ExprError>
        bool test_add(Token, Token, Token);

        template<exp_behavior, class = err::ExprError>
        bool test_unary(Token, Token);

        // makes an ExprPtr out of potentially just a token
        static void asn(ExprPtr&, Token, std::string = "default_arg");

        public:
        ExprPtrTest(Token);
        bool operator()(int&);
    };
}
#endif