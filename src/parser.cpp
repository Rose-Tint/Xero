#include "parser.hpp"


Parser::Parser(std::string fname, std::vector<std::string> used_imps)
{
    filename = fname;
    imported = used_imps;
    file = { };
    code = { };
    ast = { };
}


std::stringstream& Parser::get_code()
{
    return code;
}


void Parser::process()
{
    file.open(filename);
    while (file)
    {
        char c = file.get();
        if (c == '~')
        {
            bool is_repeat = false;
            std::string import_fname;
            for (char next_c = file.get(); next_c != '\n'; next_c = file.get())
            {
                import_fname += next_c;
            }
            import(import_fname);
        }
        else code.put(c);
    }
    file.close();
}


void Parser::import(std::string import_fname)
{
    bool is_repeat = false;
    for (auto other_imp_fname : imported)
    {
        is_repeat |= (import_fname == other_imp_fname);
    }
    if (!is_repeat)
    {
        imported.push_back(import_fname);
        Parser second_parser(import_fname, imported);
        second_parser.process();
        while (second_parser.code)
        {
            code.put(second_parser.get_code().get());
        }
    }
}


char Parser::advance(bool close)
{
    if (!(file.is_open())) file.open(filename);
    last_c = file.get();
    if (close) file.close();
    code.put(last_c);
    return last_c;
}


void Parser::parse()
{
    code.seekg(0);
    std::string ctx;
    std::vector<Token> tokens;
    while (code)
    {
        char c = code.get();
        tokens.push_back(get_token(c));
    }
}
