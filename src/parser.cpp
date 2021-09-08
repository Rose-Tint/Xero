#include "parser.hpp"


Parser::Parser(std::string fname, std::vector<std::string> used_imps)
{
    filename = fname;
    imported = used_imps;
    file = { };
    code = { };
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


bool Parser::is_identifier(char c)
{
    return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || (c == '_');
}


bool Parser::is_valid_number_char(char c)
{
    return (std::isdigit(c) || c == '.' || c == '-');
}


bool Parser::is_operator(char c)
{
    bool is_op = false;
    for (Expr expr : custom_ops)
    {
        if (expr.value[0] == c)
        {
            return true;
        }
    }
    for (std::string str : pri_ops)
    {
        if (str[0] == c)
        {
            return true;
        }
    }
    return false;
}


Expr Parser::make_number()
{
    char curr = code.peek();
    std::string num = "";
    bool is_float = false;
    while ((is_valid_number_char(curr) || curr == '_') && code.get(curr))
    {
        if (curr == '.')
        {
            if (is_float)
            {
                throw -2;
            }
            is_float = true;
            continue;
        }
        if (curr != '_')
        {
            num += curr;
        }
    }

    return { num, ((is_float) ? Expr::flo : Expr::integ) };
}


Expr Parser::make_identifier()
{
    char curr = code.peek();
    std::string id = "";
    while ((is_identifier(curr) || std::isdigit(curr)) && code.get(curr))
    {
        id += curr;
    }

    return { id, Expr::id };
}


Expr Parser::make_operator()
{
    char curr = code.peek();
    std::string op = {};
    while (is_operator(curr) && code.get(curr))
    {
        op += curr;
    }

    return { op, Expr::oper };
}


Expr* Parser::parse()
{
    code.seekg(0);
    char curr;
    while (code.get(curr))
    {
        if (std::isdigit(curr) || (curr == '-' && std::isdigit(code.peek())))
        {
            operand_stk.push(make_number());
        }
        else if (is_identifier(curr))
        {
            operand_stk.push(make_identifier());
        }
        else if (is_operator(curr))
        {
            operator_stk.push(make_operator());
        }
        else if (curr != ' ')
        {
            throw -2;
        }
    }
}

