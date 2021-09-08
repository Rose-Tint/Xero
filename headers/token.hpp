#pragma once


struct Token
{
    const char opcode;
};


constexpr Token LBRACE   { '{' };
constexpr Token RBRACE   { '}' };
constexpr Token LBRACKET { '[' };
constexpr Token RBRACKET { ']' };
constexpr Token LPAREN   { '(' };
constexpr Token RPAREN   { ')' };
constexpr Token LANGLE   { '<' };
constexpr Token RANGLE   { '>' };
constexpr Token SEMI     { ';' };
constexpr Token COLON    { ':' };
constexpr Token AMP      { '&' };
constexpr Token AT       { '@' };
constexpr Token STAR     { '*' };
constexpr Token EXCLAM   { '!' };
constexpr Token WHITESP  { ' ' };
constexpr Token PIPE     { '|' };
constexpr Token HASH     { '#' };
constexpr Token EQUALS   { '=' };
constexpr Token MOD      { '%' };
constexpr Token DASH     { '-' };
constexpr Token CARET    { '^' };
constexpr Token IDCHAR   { '_' };
constexpr Token NUM      { '0' };


Token get_token(char);
