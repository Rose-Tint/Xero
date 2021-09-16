#include "preprocessor.hpp"


std::stringstream PreProcessor::operator()(std::string main_fname)
{
    process(main_fname);
    return std::move(code);
}


void PreProcessor::process(std::string fname)
{
    bool should_process = false;
    char c;
    curr_file.open(fname);
    while (curr_file.get(c))
    {
        if (should_process)
        {
            if (c == '\n') should_process = false;
            else direct();
        }
        else if (c == '~') should_process = true;
        else code.put(c);
    }
    curr_file.close();
}


std::string PreProcessor::get_between(char left, char right)
{
    ignore_until(left);
    return get_until(right);
}


std::string PreProcessor::get_until(char c)
{
    char curr = curr_file.peek();
    std::string str;
    while (curr != c)
    {
        curr_file.get(curr);
        str += curr;
    }
    curr_file.get();
    return str;
}


void PreProcessor::direct()
{
    std::string directive = get_until(' ');
    if (directive == "import")        import();
    else if (directive == "define")   define();
    else if (directive == "ifdef")    ifdef();
    else if (directive == "ifnotdef") ifnotdef();
    else throw -2;
}


void PreProcessor::import()
{
    std::string fname = get_between('{', '}');
    if (!(imported.contains(fname)))
    {
        imported.insert(fname);
        process(fname);
    }
}


void PreProcessor::define() { defined.insert(get_between('{', '}')); }
void PreProcessor::ifdef() { if (defined.contains(get_between('{', '}'))) then(); }
void PreProcessor::ifnotdef() { if (!defined.contains(get_between('{', '}'))) then(); }


void PreProcessor::then()
{
    char c = curr_file.peek();
    while (curr_file.get(c))
    {
        if (c == '~')
        {
            std::string dir = get_until('\n');
            if (dir == "endif") break;
            else
            {
                for (int i = 0; i < dir.size(); i++) curr_file.unget();
                direct();
            }
        }
        else code.put(c);
    }
}
