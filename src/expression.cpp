#include "expression.hpp"


// NORMAL CONSTRUCTORS


Expr::Expr(const Token* tok)
    : token(tok->clone())
{
    ;
}


BinaryExpr::BinaryExpr(Token* tok, NonTerminalExpr* l, NonTerminalExpr* r)
    : NonTerminalExpr(tok->clone())
{
    left = (l != nullptr) ? l : nullptr;
    right = (r != nullptr) ? r : nullptr;
}

UnaryExpr::UnaryExpr(Token* tok, NonTerminalExpr* _operand)
    : NonTerminalExpr(tok->clone())
{
    operand = (_operand != nullptr) ? _operand : nullptr;
}

ListExpr::ListExpr(Token* tok, ListExpr* _next)
    : NonTerminalExpr(tok->clone())
{
    next = (_next != nullptr) ? _next : nullptr;
}


ParamListExpr::ParamListExpr(Token* tok, ParamListExpr* params, TypeExpr* _type, TerminalExpr* _name)
    : ListExpr(tok, params)
{
    type = _type;
    name = (_name != nullptr) ? _name : nullptr;
}


PointerExpr::PointerExpr(struct Token* tok, PointerExpr* _ptr)
    : NonTerminalExpr(tok)
{
    ptr = (_ptr != nullptr) ? _ptr : nullptr;
}


DeclaratorExpr::DeclaratorExpr(struct Token* tok, struct Token* _name, struct Token* enc_sym, TerminalExpr* arg, PointerExpr* _ptr)
    : NonTerminalExpr(tok)
{
    const_arg = (arg != nullptr) ? arg : nullptr;
    ptr = (_ptr != nullptr) ? _ptr : nullptr;
}


DeclaratorExpr::DeclaratorExpr(struct Token* tok, struct Token* _name, struct Token* enc_sym, ListExpr* args, PointerExpr* _ptr)
    : NonTerminalExpr(tok)
{
    if (dynamic_cast<ParamListExpr*>(args)) param_list = (args != nullptr) ? dynamic_cast<ParamListExpr*>(args) : nullptr;
    else arg_list = (args != nullptr) ? args : nullptr;

    switch (enc_sym->value[0])
    {
        case ('{'): enclosure_type = BRACES;   break;
        case ('('): enclosure_type = PARENS;   break;
        case ('<'): enclosure_type = ANGLES;   break;
        case ('['): enclosure_type = BRACKETS; break;
    }
}


// VIRTUAL ADD


void BinaryExpr::add(Expr* expr)
{
    auto non_terminal = dynamic_cast<NonTerminalExpr*>(expr);
    if (non_terminal)
    {
        if (left == nullptr)
        {
            left = non_terminal->clone();
            return;
        }
        else if (!(left->terminates()))
        {
            left->add(expr);
            return;
        }
        else if (right == nullptr)
        {
            right = non_terminal->clone();
            return;
        }
        else if (!(right->terminates()))
        {
            left->add(expr);
            return;
        }
    }
    delete expr;
    throw -2;
}

void UnaryExpr::add(Expr* expr)
{
    auto non_terminal = dynamic_cast<NonTerminalExpr*>(expr);
    if (non_terminal)
    {
        if (operand == nullptr)
        {
            operand = non_terminal->clone();
            return;
        }
        else if (!(operand->terminates()))
        {
            operand->add(expr);
            return;
        }
    }
    delete expr;
    throw -2;
}

void TypeExpr::add(Expr* expr)
{
    auto terminal = dynamic_cast<TerminalExpr*>(expr);
    if (terminal && name == nullptr)
    {
        name = terminal->clone();
        return;
    }
    delete expr;
    throw -2;
}

void ParamListExpr::add(Expr* expr)
{
    auto _type = dynamic_cast<TypeExpr*>(expr);
    auto _name = dynamic_cast<TerminalExpr*>(expr);
    if (_type)
    {
        if (type == nullptr)
        {
            type = _type->clone();
            return;
        }
        else if (!(type->terminates()))
        {
            type->add(expr);
            return;
        }
    }
    if (_name)
    {
        if (name == nullptr)
        {
            name = _name->clone();
            return;
        }
        else if (!(name->terminates()))
        {
            name->add(expr);
            return;
        }
    }
    delete expr;
    throw -2;
}

void PointerExpr::add(Expr* expr)
{
    auto _ptr = dynamic_cast<PointerExpr*>(expr);
    if (_ptr)
    {
        if (ptr == nullptr)
        {
            ptr = _ptr->clone();
            return;
        }
        else if (!(ptr->terminates()))
        {
            ptr->add(expr);
            return
        }
    }
    delete expr;
    throw -2;
}

// TODO: DeclaratorExpr AND ON


// RULE OF 5s
// DESTRUCTORS, COPY CTRS, COPY ASSIGNMENT OPS, MOVE CTRS, COPY ASSIGNMENT OPS


Expr::Expr(const Expr& other)
{
    delete token;
    token = (other.token != nullptr) ? other.token : nullptr;
}

Expr::Expr(Expr&& other)
{
    token = other.token;
    other.token = nullptr;
}

Expr::~Expr() { delete token; }

Expr& Expr::operator=(const Expr& other)
{
    if (this == &other) return *this;
    delete token;
    token = (other.token != nullptr) ? other.token : nullptr;
    return *this;
}

Expr& Expr::operator=(Expr&& other)
{
    if (this == &other) return *this;
    token = other.token;
    other.token = nullptr;
    return *this;
}

BinaryExpr::BinaryExpr(const BinaryExpr& other) : NonTerminalExpr(other)
{
    delete left;
    delete right;

    left = (other.left != nullptr) ? other.left : nullptr;
    right = (other.right != nullptr) ? other.right : nullptr;
}

BinaryExpr::BinaryExpr(BinaryExpr&& other) : NonTerminalExpr(other)
{
    left = other.left;
    right = other.right;

    other.left = nullptr;
    other.right = nullptr;
}

BinaryExpr::~BinaryExpr() { delete left; delete right; }

BinaryExpr& BinaryExpr::operator=(const BinaryExpr& other)
{
    delete token;
    delete left;
    delete right;

    token = (other.token != nullptr) ? other.token : nullptr;
    left = (other.left != nullptr) ? other.left : nullptr;
    right = (other.right != nullptr) ? other.right : nullptr;

    return *this;
}

BinaryExpr& BinaryExpr::operator=(BinaryExpr&& other)
{
    if (this == &other) return *this;

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

    operand = (other.operand != nullptr) ? other.operand : nullptr;
}

UnaryExpr::UnaryExpr(UnaryExpr&& other) : NonTerminalExpr(other)
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

    token = (other.token != nullptr) ? other.token : nullptr;
    operand = (other.operand != nullptr) ? other.operand : nullptr;

    return *this;
}

UnaryExpr& UnaryExpr::operator=(UnaryExpr&& other)
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
    next = (other.next != nullptr) ? other.next : nullptr;
}

ListExpr::ListExpr(ListExpr&& other) : NonTerminalExpr(other)
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

    token = (other.token != nullptr) ? other.token : nullptr;
    next = (other.next != nullptr) ? other.next : nullptr;
    return *this;
}

ListExpr& ListExpr::operator=(ListExpr&& other)
{
    if (this == &other) return *this;

    token = other.token;
    next = other.next;

    other.token = nullptr;
    other.next = nullptr;

    return *this;
}

ParamListExpr::ParamListExpr(const ParamListExpr& other) : ListExpr(other)
{
    delete name;
    delete type;

    name = (other.name != nullptr) ? other.name : nullptr;
    type = (other.type != nullptr) ? other.type : nullptr;
}

ParamListExpr::ParamListExpr(ParamListExpr&& other) : ListExpr(other)
{
    type = other.type;
    name = other.name;

    other.type = nullptr;
    other.name = nullptr;
}

ParamListExpr::~ParamListExpr() { delete type; delete name; }

ParamListExpr& ParamListExpr::operator=(const ParamListExpr& other)
{
    if (this == &other) return *this;

    delete token;
    delete type;
    delete name;

    token = (other.token != nullptr) ? other.token : nullptr;
    name = (other.name != nullptr) ? other.name : nullptr;
    type = (other.type != nullptr) ? other.type : nullptr;

    return *this;
}

ParamListExpr& ParamListExpr::operator=(ParamListExpr&& other)
{
    if (this == &other) return *this;

    token = other.token;
    type = other.type;
    name = other.name;

    other.token = nullptr;
    other.type = nullptr;
    other.name = nullptr;

    return *this;
}

PointerExpr::PointerExpr(const PointerExpr& other) : NonTerminalExpr(other)
{
    delete ptr;
    ptr = (other.ptr != nullptr) ? other.ptr : nullptr;
}

PointerExpr::PointerExpr(PointerExpr&& other) : NonTerminalExpr(other)
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

    token = (other.token != nullptr) ? other.token : nullptr;
    ptr = (other.ptr != nullptr) ? other.ptr : nullptr;

    return *this;
}

PointerExpr& PointerExpr::operator=(PointerExpr&& other)
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
    delete ptr;
    delete arg_list;
    delete const_arg;
    delete param_list;

    ptr = (other.ptr != nullptr) ? other.ptr : nullptr;
    arg_type = other.arg_type;
    enclosure_type = other.enclosure_type;

    switch (arg_type)
    {
        case (CONSTARG):
            const_arg = (other.const_arg != nullptr) ? other.const_arg : nullptr;
            break;
        case (ARGLIST):
            arg_list = (other.arg_list != nullptr) ? other.arg_list : nullptr;
            break;
        case (PARAMLIST):
            param_list = (other.param_list != nullptr) ? other.param_list : nullptr;
            break;
    }
}

DeclaratorExpr::DeclaratorExpr(DeclaratorExpr&& other) : NonTerminalExpr(other)
{
    ptr = other.ptr;
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
}

DeclaratorExpr::~DeclaratorExpr()
{
    delete ptr;
    delete arg_list;
    delete const_arg;
    delete param_list;
}

DeclaratorExpr& DeclaratorExpr::operator=(const DeclaratorExpr& other)
{
    if (this == &other) return *this;

    delete token;
    delete ptr;
    delete arg_list;
    delete const_arg;
    delete param_list;

    token = (other.token != nullptr) ? other.token : nullptr;
    ptr = (other.ptr != nullptr) ? other.ptr : nullptr;
    arg_type = other.arg_type;
    enclosure_type = other.enclosure_type;

    switch (arg_type)
    {
        case (CONSTARG):
            const_arg = (other.const_arg != nullptr) ? other.const_arg : nullptr;
            break;
        case (ARGLIST):
            arg_list = (other.arg_list != nullptr) ? other.arg_list : nullptr;
            break;
        case (PARAMLIST):
            param_list = (other.param_list != nullptr) ? other.param_list : nullptr;
            break;
    }

    return *this;
}

DeclaratorExpr& DeclaratorExpr::operator=(DeclaratorExpr&& other)
{
    if (this == &other) return *this;

    ptr = other.ptr;
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

    return *this;
}
