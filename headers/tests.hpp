#ifndef TESTS_HPP
#include <iostream>

#include "expression.hpp"

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
        std::ostream out;
        ExprPtr ref;

        class NoErr { };

        template<exp_behavior, class = NoErr>
        bool test_add(Token, Token, Token) const;

        template<exp_behavior, class = NoErr>
        bool test_unary(Token, Token) const;

        // makes an ExprPtr out of potentially just a token
        static void asn(ExprPtr&, Token, std::string = "default_arg");

        public:
        ExprPtrTest(Token, const std::ostream& = std::cout);
        bool operator()(int&);
    };
}
#endif