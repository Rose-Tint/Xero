#include <string>
#include <sstream>
#include <vector>
#include "headers/preprocessor.hpp"
#include "headers/lexer.hpp"
#include "headers/parser.hpp"
#include "headers/token.hpp"


int main(int argc, char** argv)
{
    std::string main_fname(argv[1]);
    PreProcessor pre_pro {};
    Parser parser {};
    std::stringstream& sstream = pre_pro(main_fname);
    std::vector<token_t> tokens = lex(sstream);
    expr_t* AST = parser(tokens);
}
