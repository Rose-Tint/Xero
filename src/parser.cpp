#include "parser.hpp"
#include <cctype>


void Parser::process(std::string fname)
{
    bool should_process = false;
    file.open(fname);
    char c = file.peek();
    std::string str {};
    while (file.get(c))
    {
        if (should_process)
        {
            if (c == '~')
            {
                should_process = false;
                str.clear();
                continue;
            }
            else if (c == ' ')
            {
                if (str == "import")
                {
                    str.clear();
                    while (c == ' ') file.get(c);
                    while (std::isalpha(c))
                    {
                        file.get(c);
                        str += c;
                    }
                    if (!imported.find(import_fname))
                    {
                        imported.push_back(import_fname);
                        process(import_fname);
                    }
                }
                // ADD OTHER PREPROCESSING DIRECTIVES HERE
            }
            else if (std::isalpha(c)) str += c;
            else throw -2;
        }
        else if (c == '~') should_process = true;
        else code.put(c);
    }
    file.close();
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
    for (oper_t op : custom_ops)
    {
        if (expr_t.value[0] == c)
        {
            return true;
        }
    }
    return (pri_ops.find(c));
}


expr_t Parser::make_number()
{
    char curr = code.peek();
    std::string num {};
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

    return { num, ((is_float) ? expr_t::flo : expr_t::integ) };
}


expr_t Parser::make_identifier()
{
    char curr = code.peek();
    std::string id {};
    while ((is_identifier(curr) || std::isdigit(curr)) && code.get(curr))
    {
        id += curr;
    }

    return { id, expr_t::id };
}


oper_t Parser::make_operator()
{
    char curr = code.peek();
    std::string op = {};
    while (is_operator(curr) && code.get(curr))
    {
        op += curr;
    }

    return { op };
}


expr_t* Parser::parse()
{
    code.seekg(0);
    char curr = code.peek();
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

