#pragma once

#include <string>
#include <unordered_map>


enum TokenType
{
    IDENTIFIER,
    KEYWORD,
    SYMBOL,
    ENCAP,
    ENDL,
    UNOP,
    BIOP,
    ASSOP,
    LITERAL
};


const std::unordered_map<char, TokenType> symbols
{
    { '{' , ENCAP  }, { '}'  , ENCAP  },
    { '[' , ENCAP  }, { ']'  , ENCAP  },
    { ':' , SYMBOL }, { '('  , ENCAP  },
    { ')' , ENCAP  }, { '"'  , ENCAP  },
    { ';' , ENDL   }, { '\'' , ENCAP  },
};

const std::unordered_map<std::string, TokenType> operators
{
    { "!"  , UNOP  }, { "@"  , UNOP  },
    { "#"  , UNOP  }, { "-"  , UNOP  },
    { "^"  , BIOP  }, { "&"  , BIOP  },
    { "*"  , BIOP  }, { "%"  , BIOP  },
    { "+"  , BIOP  }, { "<"  , BIOP  },
    { ">"  , BIOP  }, { ","  , BIOP  },
    { "."  , BIOP  }, { "/"  , BIOP  },
    { "|"  , BIOP  }, { "<=" , BIOP  },
    { ">=" , BIOP  }, { "!=" , BIOP  },
    { "++" , BIOP  }, { "--" , BIOP  },
    { "="  , BIOP  }, { ":=" , ASSOP },
    { "%=" , ASSOP }, { "^=" , ASSOP },
    { "*=" , ASSOP }, { "-=" , ASSOP },
    { "+=" , ASSOP }, { "/=" , ASSOP },
    { "&=" , ASSOP }, { "|=" , ASSOP },
    { "::" , ASSOP },
};


struct token_t
{
    const TokenType type;
    const std::string value;
    bool is_final() const { return (type == IDENTIFIER) || (type == LITERAL); }
    token_t operator=(const token_t& other) { return  { other.type, other.value }; }
};