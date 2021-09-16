#include <string>
#include <iostream>

#include "error.hpp"
#include "preprocessor.hpp"
#include "token.hpp"
#include "lexer.hpp"
#include "expression.hpp"
#include "scope.hpp"
#include "parser.hpp"


int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "file required" << std::endl;
        return 0;
    }

    std::stringstream code;
    PreProcessor pp;

    try
    {
        code = pp(std::string(argv[1]));
        Parser psr(code);
        auto expr_tree = psr();
        std::cout << expr_tree << std::endl;
    }
    catch (err::ParserError e)
    {
        std::cout << "Parsing Error: " << e.what() << std::endl;
        return 0;
    }
    catch (err::LexerError e)
    {
        std::cout << "Lexing Error: " << e.what() << std::endl;
        return 0;
    }
    catch (err::SyntaxError e)
    {
        std::cout << "Syntax Error: " << e.what() << std::endl;
        return 0;
    }
    catch (err::PreProcessorError e)
    {
        std::cout << "No Arg Error: " << e.what() << std::endl;
        return 0;
    }
}