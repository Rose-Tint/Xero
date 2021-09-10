#pragma once

#include <string>
#include <unordered_map>


enum TokenType
{
    IDENTIFIER,
    KEYWORD,
    SYMBOL,
    ENDL,
    UNOP,
    BIOP,
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
    { "!"  , UNOP }, { "@"  , UNOP },
    { "#"  , UNOP }, { "-"  , UNOP },
    { "^"  , BIOP }, { "&"  , BIOP },
    { "*"  , BIOP }, { "%"  , BIOP },
    { "+"  , BIOP }, { "<"  , BIOP },
    { ">"  , BIOP }, { ","  , BIOP },
    { "."  , BIOP }, { "/"  , BIOP },
    { "|"  , BIOP }, { "<=" , BIOP },
    { ">=" , BIOP }, { "!=" , BIOP },
    { "++" , BIOP }, { "--" , BIOP },
    { "="  , BIOP }, { ":=" , BIOP },
    { "%=" , BIOP }, { "^=" , BIOP },
    { "*=" , BIOP }, { "-=" , BIOP },
    { "+=" , BIOP }, { "/=" , BIOP },
    { "&=" , BIOP }, { "|=" , BIOP },
    { "::" , BIOP },
};


struct token_t
{
    const TokenType type;
    const std::string value;
    bool is_final() const { return (type == IDENTIFIER) || (type == LITERAL); }
    token_t operator=(const token_t&) = default;
    bool operator==(const token_t& other) const { return type == other.type && value == other.value; }
};


const token_t STRUCT { KEYWORD , "struct" };
const token_t FN     { KEYWORD , "fn" };
const token_t IF     { KEYWORD , "if" };
const token_t ELSE   { KEYWORD , "else" };
const token_t FOR    { KEYWORD , "for" };
const token_t OVER   { KEYWORD , "over" };
const token_t WHILE  { KEYWORD , "while" };
const token_t ALIAS  { KEYWORD , "alias" };
const token_t TRUE   { KEYWORD , "true" };
const token_t FALSE  { KEYWORD , "false" };

