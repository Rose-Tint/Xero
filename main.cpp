#include <string>

#include "preprocessor.hpp"
#include "token.hpp"
#include "lexer.hpp"
#include "expression.hpp"
#include "scope.hpp"
#include "parser.hpp"


int main(int argc, char** argv)
{
    if (argc < 2) return -2;

    std::stringstream code;
    PreProcessor pp;

    code = pp(std::string(argv[1]));
    Parser psr(code);
    Expr expr_tree = psr();

    std::cout << expr_tree << std::endl;

    return 0;
}