#include "preprocessor.hpp"


typedef std::unordered_set<std::string> str_set;


void PreProcessor::process(std::string fname)
{
    bool should_process = false;
    std::ifstream file(fname);
    char c = 0;
    while (file.get(c))
    {
        if (should_process)
        {
            if (c == '\n') should_process = false;
            else direct(file);
        }
        else if (c == '~') should_process = true;
        else code.put(c);
    }
    file.close();
}


std::string PreProcessor::get_between(std::ifstream& file, char left, char right)
{
    ignore_until(file, left);
    return get_until(file, right);
}


std::string PreProcessor::get_until(std::ifstream& file, char c)
{
    char curr = file.peek();
    std::string str = "";
    while (curr != c)
    {
        file.get(curr);
        str += curr;
    }
    return str;
}


void PreProcessor::ignore_until(std::ifstream& file, char c)
{
    while (file.get() != c);
}


void PreProcessor::direct(std::ifstream& file)
{
    std::string directive = get_until(file, ' ');
    if (directive == "import")
    {
        import(file);
    }
    else if (directive == "define")
    {
        define(file);
    }
    else if (directive == "ifdef")
    {
        ifdef(file);
    }
    else if (directive == "ifnotdef")
    {
        ifnotdef(file);
    }
    else throw -2;
}


void PreProcessor::import(std::ifstream& file)
{
    std::string fname = get_between(file, '{', '}');
    if (!(imported.contains(fname)))
    {
        imported.insert(fname);
        process(fname);
    }
}


void PreProcessor::define(std::ifstream& file)
{
    std::string def = get_between(file, '{', '}');
    defined.insert(def);
}


void PreProcessor::ifdef(std::ifstream& file)
{
    if (defined.contains(get_between(file, '{', '}'))) then(file);
}


void PreProcessor::ifnotdef(std::ifstream& file)
{
    if (!(defined.contains(get_between(file, '{', '}')))) then(file);
}


void PreProcessor::then(std::ifstream& file)
{
    char c = file.get();
    while (file.get(c))
    {
        if (c == '~')
        {
            std::string dir = get_until(file, ' ');
            if (dir == "endif") break;
            else
            {
                for (int i = 0; i < 5; i++) file.unget();
                direct(file);
            }
        }
        code.put(c);
    }
}
