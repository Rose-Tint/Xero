#include <sstream>
#include <string>
#include <string>
#include <iostream>

#include "error.hpp"
#include "preprocessor.hpp"
#include "parser.hpp"

#ifdef X_TESTS
#define X_BLANK_S "__BLANK_TEST__"
int main(void)
{
    // ExprPtr tests
    // syntactically correct
    test_ExprPtr<ASN, ID, NUM>();
    test_ExprPtr<ADD, NUM, NUM

    // syntactically incorrect
    test_ExprPtr<ADD, NUM, LBRACE>(); // should throw an error
    test_ExprPtr<NUM, XOR, EXIT>(); // should also throw an error
    test_ExprPtr<ID, ENTRY, SUB>(); // should throw an error
}
#else
int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "filename required" << std::endl;
        return 0;
    }
    try
    {
        std::stringstream code;
        PreProcessor pp;
        code = pp(std::string(argv[1]));
        Parser psr(code);
        ExprPtr expr_tree = psr();
        std::cout << expr_tree << std::endl;
    }
    catch (err::ParserError e)       { std::cout<<"Parser Error: "<<e.what()<<std::endl; }
    catch (err::LexerError e)        { std::cout<<"Lexing Error: "<<e.what()<<std::endl; }
    catch (err::SyntaxError e)       { std::cout<<"Syntax Error: "<<e.what()<<std::endl; }
    catch (err::PreProcessorError e) { std::cout<<"No Arg Error: "<<e.what()<<std::endl; }
}
#endif