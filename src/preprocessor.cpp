#include "preprocessor.hpp"


void process(std::string fname)
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