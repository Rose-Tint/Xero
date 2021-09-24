#include "token.hpp"

const char* ttos(Token t)
{
    switch (t)
    {
        case EXIT:     return "EXIT";
        case ENTRY:    return "ENTRY";
        case NUM:      return "NUM";
        case STR:      return "STR";
        case ID:       return "ID";
        case EMPTY:    return "EMPTY";
        case LPAREN:   return "LPAREN";
        case RPAREN:   return "RPAREN";
        case NOT:      return "NOT";
        case AND:      return "AND";
        case OR:       return "OR";
        case XOR:      return "XOR";
        case EQ:       return "EQ";
        case GT:       return "GT";
        case LT:       return "LT";
        case MOD:      return "MOD";
        case DIV:      return "DIV";
        case MUL:      return "MUL";
        case PLUS:     return "PLUS";
        case MINUS:    return "MINUS";
        case ASN:      return "ASN";
        case LBRACE:   return "LBRACE";
        case RBRACE:   return "RBRACE";
        case LBRACKET: return "LBRACKET";
        case RBRACKET: return "RBRACKET";
        case ENDL:     return "ENDL";
    }
}


bool is_terminal(Token token)
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
