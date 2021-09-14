#include "expression.hpp"


// RULE OF 5s
// DESTRUCTORS, COPY CTRS, COPY ASSIGNMENT OPS, MOVE CTRS, COPY ASSIGNMENT OPS


Expr::Expr(const Expr& other)
{
    delete token;
    token = (other.token != nullptr) ? other.token->clone() : nullptr;
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
    token = (other.token != nullptr) ? other.token->clone() : nullptr;
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

    left = (other.left != nullptr) ? other.left->clone() : nullptr;
    right = (other.right != nullptr) ? other.right->clone() : nullptr;
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

    token = (other.token != nullptr) ? other.token->clone() : nullptr;
    left = (other.left != nullptr) ? other.left->clone() : nullptr;
    right = (other.right != nullptr) ? other.right->clone() : nullptr;

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

    operand = (other.operand != nullptr) ? other.operand->clone() : nullptr;
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

    token = (other.token != nullptr) ? other.token->clone() : nullptr;
    operand = (other.operand != nullptr) ? other.operand->clone() : nullptr;

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
    next = (other.next != nullptr) ? other.next->clone() : nullptr;
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

    token = (other.token != nullptr) ? other.token->clone() : nullptr;
    next = (other.next != nullptr) ? other.next->clone() : nullptr;
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

    name = (other.name != nullptr) ? other.name->clone() : nullptr;
    type = (other.type != nullptr) ? other.type->clone() : nullptr;
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

    token = (other.token != nullptr) ? other.token->clone() : nullptr;
    name = (other.name != nullptr) ? other.name->clone() : nullptr;
    type = (other.type != nullptr) ? other.type->clone() : nullptr;

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
    ptr = (other.ptr != nullptr) ? other.ptr->clone() : nullptr;
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

    token = (other.token != nullptr) ? other.token->clone() : nullptr;
    ptr = (other.ptr != nullptr) ? other.ptr->clone() : nullptr;

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

    ptr = (other.ptr != nullptr) ? other.ptr->clone() : nullptr;
    arg_type = other.arg_type;
    enclosure_type = other.enclosure_type;

    switch (arg_type)
    {
        case (CONSTARG):
            const_arg = (other.const_arg != nullptr) ? other.const_arg->clone() : nullptr;
            break;
        case (ARGLIST):
            arg_list = (other.arg_list != nullptr) ? other.arg_list->clone() : nullptr;
            break;
        case (PARAMLIST):
            param_list = (other.param_list != nullptr) ? other.param_list->clone() : nullptr;
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

    token = (other.token != nullptr) ? other.token->clone() : nullptr;
    ptr = (other.ptr != nullptr) ? other.ptr->clone() : nullptr;
    arg_type = other.arg_type;
    enclosure_type = other.enclosure_type;

    switch (arg_type)
    {
        case (CONSTARG):
            const_arg = (other.const_arg != nullptr) ? other.const_arg->clone() : nullptr;
            break;
        case (ARGLIST):
            arg_list = (other.arg_list != nullptr) ? other.arg_list->clone() : nullptr;
            break;
        case (PARAMLIST):
            param_list = (other.param_list != nullptr) ? other.param_list->clone() : nullptr;
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
