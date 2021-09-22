#include "tests.hpp"


int main()
{
    int indent = 0;
    tst::ExprPtrTest expr_ptr_test(MUL);
    expr_ptr_test(indent);
    return 0;
}
