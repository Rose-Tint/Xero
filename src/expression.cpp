#include "headers/expression.hpp"


// NORMAL CONSTRUCTORS


Expr::Expr(Token* tok) : token(tok->clone())
{
    ;
}


BinaryOperationExpr::BinaryOperationExpr(Token* tok, NonTerminalExpr* l, NonTerminalExpr* r)
    : NonTerminalExpr(tok->clone())
{
    left = safe_clone(l);
    right = safe_clone(r);
}

UnaryOperationExpr::UnaryOperationExpr(Token* tok, NonTerminalExpr* _operand)
    : NonTerminalExpr(tok->clone())
{
    operand = safe_clone(_operand);
}

ListExpr::ListExpr(Token* tok, ListExpr* _next)
    : NonTerminalExpr(tok->clone())
{
    next = safe_clone(next);
}


ParamListExpr::ParamListExpr(Token* tok, Type* _type, TerminalExpr* _name, ParamListExpr* params)
    : ListExpr(tok, params)
{
    type = _type;
    name = safe_clone(params);
}


PointerExpr(Token* tok, Token* _ptr)
    : NonTerminalExpr(tok)
{
    ptr = safe_clone(_ptr);
}


DeclaratorExpr(Token* tok, Token* _name, Token* enc_sym, TerminalExpr* arg, PointerExpr* _ptr)
    : NonTerminalExpr(tok)
{
    name = safe_clone(_name);
    const_arg = safe_clone(arg);
    ptr = safe_clone(_ptr);
}


DeclaratorExpr(Token* tok, Token* _name, Token* enc_sym, ListExpr* args, PointerExpr* _ptr)
    : NonTerminalExpr(tok)
{
    if (dynamic_cast<ParamListExpr>(args)) param_list = safe_clone(args);
    else arg_list = safe_clone(args);

    switch (enc_sym.value)
    {
        case ("{"): enc_type = BRACES; break;
        case ("("): enc_type = PARENS; break;
        case ("<"): enc_type = ANGLES; break;
        case ("["): enc_type = BRACKETS; break;
    }
}


// RULE OF 5s
// DESTRUCTORS, COPY CTRS, COPY ASSIGNMENT OPS, MOVE CTRS, COPY ASSIGNMENT OPS


Expr::Expr(const Expr& other)
{
    delete token;
    token = safe_clone(other.token);
}

Expr::Expr(const Expr&& other)
{
    token = other.token;
    other.token = nullptr;
}

Expr::~Expr() { delete token; }

Expr& Expr::operator=(const Expr& other)
{
    if (this = &other) return *this;
    delete token;
    token = safe_clone(other.token);
    return *this;
}

Expr& Expr::operator=(const Expr&& other)
{
    if (this == &other) return *this;
    token = other.token;
    other.token = nullptr;
    return *this;
}

BinaryOperationExpr::BinaryOperationExpr(const BinaryOperationExpr& other) : NonTerminalExpr(other)
{
    delete left;
    delete right;

    left = safe_clone(other.left);
    right = safe_clone(other.right);
}

BinaryOperationExpr::BinaryOperationExpr(const BinaryOperationExpr&& other) : NonTerminalExpr(other)
{
    left = other.left;
    right = other.right;

    other.left = nullptr;
    other.right = nullptr;
}

BinaryOperationExpr::~BinaryOperationExpr() { delete left; delete right; }

BinaryOperationExpr& BinaryOperationExpr::operator=(const BinaryOperationExpr& other)
{
    delete token;
    delete left;
    delete right;

    token = safe_clone(other.token);
    left = safe_clone(other.left);
    right = safe_clone(other.right);

    return *this;
}

BinaryOperationExpr& BinaryOperationExpr::operator=(const BinaryOperationExpr&& other)
{
    if (this = &other) return *this;

    token = other.token;
    left = other.left;
    right = other.right;

    other.token = nullptr;
    other.left = nullptr;
    other.right = nullptr;

    return *this;
}

UnaryExpr::UnaryExpr(const UnaryExpr& other) : NonTerminalExpr(other)
{
    delete operand;

    operand = safe_clone(other.operand);
}

UnaryExpr::UnaryExpr(const UnaryExpr&& other) : NonTerminalExpr(other)
{
    operand = other.operand;

    other.operand = nullptr;
}

UnaryExpr::~UnaryExpr() { delete operand; }

UnaryExpr& UnaryExpr::operator=(const UnaryExpr& other)
{
    if (this == &other) return *this;

    delete operand;
    delete token;

    token = safe_clone(other.token);
    operand = safe_clone(other.operand);

    return *this;
}

UnaryExpr& UnaryExpr::operator=(const UnaryExpr&& other)
{
    if (this == &other) return *this;

    token = other.token;
    operand = other.operand;

    other.token = nullptr;
    other.operand = nullptr;

    return *this;
}

ListExpr::ListExpr(const ListExpr& other) : NonTerminalExpr(other)
{
    delete next;
    next = safe_clone(other.next);
}

ListExpr::ListExpr(const ListExpr&& other) : NonTerminalExpr(other)
{
    next = other.next;
    other.next = nullptr;
}

ListExpr::~ListExpr() { delete next; }

ListExpr& ListExpr::operator=(const ListExpr& other)
{
    if (this == &other) return *this;

    delete token;
    delete next;

    token = safe_clone(other.token);
    next = safe_clone(other.next);
    return *this;
}

ListExpr& ListExpr::operator=(const ListExpr&& other)
{
    if (this == &other) return *this;

    token = other.token;
    next = other.next;

    other.token = nullptr;
    other.next = nullptr;

    return *this;
}

ParamListExpr::ParamListExpr(const ParamListExpr& other) : NonTerminalExpr(other)
{
    delete identifier;
    delete type;

    identifier = safe_clone(other.identifier);
    type = safe_clone(other.type);
}

ParamListExpr::ParamListExpr(const ParamListExpr&& other) : NonTerminalExpr(other)
{
    type = other.type;
    identifier = other.identifier;

    other.type = nullptr;
    other.identifier = nullptr;
}

ParamListExpr::~ParamListExpr() { delete type; delete identifier; }

ParamListExpr& ParamListExpr::operator=(const ParamListExpr& other)
{
    if (this == &other) return *this;

    delete token;
    delete type;
    delete identifier;

    token = safe_clone(other.token);
    identifier = safe_clone(other.identifier);
    type = safe_clone(other.type);

    return *this;
}

ParamListExpr& ParamListExpr::operator=(const ParamListExpr&& other)
{
    if (this == &other) return *this;

    token = other.token;
    type = other.type;
    identifier = other.identifier;

    other.token = nullptr;
    other.type = nullptr;
    other.identifier = nullptr;

    return *this;
}

PointerExpr::PointerExpr(const PointerExpr& other) : NonTerminalExpr(other)
{
    delete ptr;
    ptr = safe_clone(other.ptr);
}

PointerExpr::PointerExpr(const PointerExpr&& other)
{
    ptr = other.ptr;
    other.ptr = nullptr;
}

PointerExpr::~PointerExpr() { delete token; }

PointerExpr& PointerExpr::operator=(const PointerExpr& other)
{
    if (this == &other) return *this;

    delete token;
    delete ptr;

    token = safe_clone(other.token);
    ptr = safe_clone(other.ptr);

    return *this;
}

PointerExpr& PointerExpr::operator=(const PointerExpr&& other)
{
    if (this == &other) return *this;

    token = other.token;
    ptr = other.ptr;

    other.token = nullptr;
    other.ptr = nullptr;

    return *this;
}

DeclaratorExpr::DeclaratorExpr(const DeclaratorExpr& other) : NonTerminalExpr(other)
{
    delete name;
    delete ptr;
    delete arg_list;
    delete const_arg;
    delete param_list;

    name = safe_clone(other.name);
    ptr = safe_clone(other.ptr);
    arg_type = other.arg_type;
    enclosure_type = other.enclosure_type;

    switch (arg_type)
    {
        case (CONSTARG):
            const_arg = safe_clone(other.const_arg);
            break;
        case (ARGLIST):
            arg_list = safe_clone(other.arg_list);
            break;
        case (PARAMLIST):
            param_list = safe_clone(other.param_list);
            break;
    }
}

DeclaratorExpr::DeclaratorExpr(const DeclaratorExpr&& other)
{
    ptr = other.ptr;
    name = other.name;
    arg_type = other.arg_type;
    enclosure_type = other.enclosure_type;
    switch (other.arg_type)
    {
        case (CONSTARG):
            const_arg = other.const_arg;
            other.const_arg = nullptr;
            break;
        case (ARGLIST):
            arg_list = other.arg_list;
            other.arg_list = nullptr;
            break;
        case (PARAMLIST):
            param_list = other.param_list;
            other.param_list = nullptr;
            break;
    }

    other.ptr = nullptr;
    other.name = nullptr;
}

DeclaratorExpr::~DeclaratorExpr()
{
    delete name;
    delete ptr;
    delete arg_list;
    delete const_arg;
    delete param_list;
}

DeclaratorExpr& DeclaratorExpr::operator=(const DeclaratorExpr& other)
{
    if (this == &other) return *this;

    delete token;
    delete name;
    delete ptr;
    delete arg_list;
    delete const_arg;
    delete param_list;

    token = safe_clone(token);
    name = safe_clone(other.name);
    ptr = safe_clone(other.ptr);
    arg_type = other.arg_type;
    enclosure_type = other.enclosure_type;

    switch (arg_type)
    {
        case (CONSTARG):
            const_arg = safe_clone(other.const_arg);
            break;
        case (ARGLIST):
            arg_list = safe_clone(other.arg_list);
            break;
        case (PARAMLIST):
            param_list = safe_clone(other.param_list);
            break;
    }

    return *this;
}

DeclaratorExpr& DeclaratorExpr::operator=(const DeclaratorExpr&& other)
{
    if (this == &other) return *this;

    ptr = other.ptr;
    name = other.name;
    arg_type = other.arg_type;
    enclosure_type = other.enclosure_type;
    switch (other.arg_type)
    {
        case (CONSTARG):
            const_arg = other.const_arg;
            other.const_arg = nullptr;
            break;
        case (ARGLIST):
            arg_list = other.arg_list;
            other.arg_list = nullptr;
            break;
        case (PARAMLIST):
            param_list = other.param_list;
            other.param_list = nullptr;
            break;
    }

    other.token = nullptr;
    other.ptr = nullptr;
    other.name = nullptr;

    return *this;
}
