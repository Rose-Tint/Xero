#ifndef TESTS_HPP
#define TESTS_HPP

#include <vector>
#include <fstream>

#include "expression.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "error.hpp"


namespace tst
{
    class TestBase;
    class ExprPtrTest;
    class LexerTest;
    enum exp_behavior { THROW, EQUATE };

    typedef bool (TestBase::*TestFunction)(void);

    class TestBase
    {
        static std::vector<std::streambuf*> bstack;

        protected:
        static std::vector<TestBase*> tests;
        TestBase() { tests.push_back(this); }

        virtual bool run() = 0;

        template<typename ...Args>
        static void print(std::string, Args...);
        template<typename>
        static void print(std::string);

        static void newl() { print_stack("\n"); }

        public:
        static bool run_tests();
        static void print_stack(const std::string&);
        static void reg(std::streambuf*);
        static unsigned char idt;
    };

    class ExprPtrTest final : private virtual TestBase
    {
        static ExprPtr ref;
        template<exp_behavior, class = err::ExprError>
        bool test_add(Token, Token, Token);

        template<exp_behavior, class = err::ExprError>
        bool test_unary(Token, Token);

        // if the token would cause an ExprPtr to use a value arg, uses the given arg
        static ExprPtr asn(Token, std::string = "default_arg");
        bool run() override final;

        public:
        using TestBase::TestBase;
    };

    class LexerTest final : private virtual TestBase
    {
        bool test_next(std::string, std::vector<Token>);
        bool run() override final;

        public:
        using TestBase::TestBase;
    };
}

#endif