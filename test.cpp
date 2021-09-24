#include <iostream>
#include <cstdio>
#include <ctime>
#include "headers/tests.hpp"


using std::ios_base;


int main()
{
    tst::TestBase::reg(std::cout.rdbuf());
#ifdef LOG_TESTS
    std::fstream logfile("test-log.log", ios_base::app);
    tst::TestBase::reg(logfile.rdbuf());
#endif

    auto t = std::time(nullptr);
    tst::TestBase::print_stack(std::ctime(&t));
    tst::TestBase::idt++;

    tst::ExprPtrTest expr_ptr_test;
    tst::LexerTest lxr_test;

    tst::TestBase::run_tests();

    std::cout << std::endl;
}
