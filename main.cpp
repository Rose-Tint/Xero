#include <string>
#include <sstream>
#include "headers/preprocessor.hpp"
#include "headers/lexer.hpp"
#include "headers/parser.hpp"
#include "headers/token.hpp"


int main(int argc, char** argv)
{
    PreProcessor pre_pro();
    std::string main_fname;

    main_fname = argv[1];
    std::stringstream code = pre_pro(main_fname);
    expr_t ast = parse(code);

    return 0;
}
