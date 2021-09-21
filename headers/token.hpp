#ifndef TOKEN_HPP
#define TOKEN_HPP
enum Token : char
{
    EXIT     =  0 ,
    ENTRY    = -1 ,
    NUM      = -2 ,
    ID       = -4 ,
    EMPTY    = -5,
    LPAREN   = '(',
    RPAREN   = ')',
    NOT      = '!',
    AND      = '&',
    OR       = '|',
    XOR      = '^',
    EQ       = '=',
    GT       = '>',
    LT       = '<',
    MOD      = '%',
    DIV      = '/',
    MUL      = '*',
    PLUS     = '+',
    MINUS    = '-',
    ASN      = ':',
    LBRACE   = '{',
    RBRACE   = '}',
    ENDL     = ';',
};
inline bool is_terminal(const Token& token)
{
    switch (token)
    {
        case ID:
        case NUM:
        case EXIT:
        case EMPTY:
        case ENDL:
            return true;
        default:
            return false;
    }
}
#endif