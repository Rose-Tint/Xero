#pragma once

#include "type.hpp"
#include "scope.hpp"
#include "token.hpp"


typedef unsigned char id_t;


struct Expr
{
    virtual id_t id() const { return EXPR; };

    explicit Expr(Token*);

    virtual ~Expr();
    Expr(const Expr&);
    Expr(const Expr&&);
    Expr& operator=(const Expr&);
    Expr& operator=(const Expr&&);

    Expr() = delete;

    Expr* get_token() const { return token; }

    protected:
    static Expr* safe_clone(const Expr* expr) { return (expr != nullptr) ? expr->clone() : nullptr; }
    virtual Expr* clone() const override { return new Expr(*this); }
    Token* token;
};


struct NonTerminalExpr : Expr
{
    virtual id_t id() const override { return NONTERMINAL_EXPR; };

    protected:
    NonTerminalExpr(Token* tok) : Expr(tok) { }
    NonTerminalExpr(const NonTerminalExpr& other) : Expr(other) { }
    NonTerminalExpr(const NonTerminalExpr&& other) : Expr(other) { }
    virtual NonTerminalExpr* clone() const override { return new NonTerminalExpr(*this); }
};


struct TerminalExpr : NonTerminalExpr
{
    virtual id_t id() const override { return TERMINAL_EXPR; };

    protected:
    TerminalExpr(Token* tok) : NonTerminalExpr(tok) { }
    TerminalExpr(const TerminalExpr& other) : NonTerminalExpr(other) { }
    TerminalExpr(const TerminalExpr&& other) : NonTerminalExpr(other) { }
    virtual TerminalExpr* clone() const override { return new TerminalExpr(*this); }
};


struct BinaryOperationExpr final : NonTerminalExpr
{
    virtual id_t id() const override { return BINARY_EXPR; };

    virtual ~BinaryOperationExpr() override;
    BinaryOperationExpr(const BinaryOperationExpr&);
    BinaryOperationExpr(const BinaryOperationExpr&&);
    BinaryOperationExpr& operator=(const BinaryOperationExpr&);
    BinaryOperationExpr& operator=(const BinaryOperationExpr&&);

    BinaryOperationExpr(Token*, NonTerminalExpr* = nullptr, NonTerminalExpr* = nullptr);

    NonTerminalExpr* get_left() const { return left; }
    NonTerminalExpr* get_right() const { return right; }

    protected:
    virtual BinaryOperationExpr* clone() const override { return new BinaryOperationExpr(*this); }
    NonTerminalExpr* left;
    NonTerminalExpr* right;
};


struct UnaryOperationExpr final : NonTerminalExpr
{
    virtual id_t id() const override { return UNARY_EXPR; };

    virtual ~UnaryOperationExpr() override;
    UnaryOperationExpr(const UnaryOperationExpr&);
    UnaryOperationExpr(const UnaryOperationExpr&&);
    UnaryOperationExpr& operator=(const UnaryOperationExpr&);
    UnaryOperationExpr& operator=(const UnaryOperationExpr&&);

    UnaryOperationExpr(Token*, NonTerminalExpr* = nullptr);

    NonTerminalExpr* get_operand() const { return operand; }

    protected:
    virtual UnaryOperationExpr* clone() const override { return new UnaryOperationExpr(*this); }
    NonTerminalExpr* operand;
};


struct ListExpr : NonTerminalExpr
{
    virtual id_t id() const override { return LIST_EXPR; };

    virtual ~ListExpr() override;
    ListExpr(const ListExpr&);
    ListExpr(const ListExpr&&);
    ListExpr& operator=(const ListExpr&);
    ListExpr& operator=(const ListExpr&&);

    ListExpr(Token*, ListExpr* = nullptr);

    ListExpr* get_next() const { return next; }

    protected:
    virtual ListExpr* clone() const override { return new ListExpr(*this); }
    ListExpr* next;
};


struct ParamListExpr final : ListExpr
{
    virtual id_t id() const override { return PARAM_LIST_EXPR; };

    virtual ~ParamListExpr() override;
    ParamListExpr(const ParamListExpr&);
    ParamListExpr(const ParamListExpr&&);
    ParamListExpr& operator=(const ParamListExpr&);
    ParamListExpr& operator=(const ParamListExpr&&);

    ParamListExpr(Token*, Type*, TerminalExpr* = nullptr, ParamListExpr* = nullptr);

    Type* get_type() const { return type; }
    TerminalExpr* get_name() const { return name; }

    protected:
    virtual ParamListExpr* clone() const override { return new ParamListExpr(*this); }
    Type* type;
    TerminalExpr* name;
};


struct PointerExpr final : NonTerminalExpr
{
    virtual id_t id() const override { return POINTER_EXPR; };

    virtual ~PointerExpr() override;
    PointerExpr(const PointerExpr&);
    PointerExpr(const PointerExpr&&);
    PointerExpr& operator=(PointerExpr&);
    PointerExpr& operator=(PointerExpr&&);

    PointerExpr(Token*, Token* = nullptr);

    protected:
    virtual PointerExpr* clone() const override { return new PointerExpr(*this); }
    PointerExpr* ptr;
};


struct DeclaratorExpr final : NonTerminalExpr
{
    virtual id_t id() const override { return DECLARATOR_EXPR; };

    virtual ~DeclaratorExpr() override;
    DeclaratorExpr(const DeclaratorExpr&);
    DeclaratorExpr(const DeclaratorExpr&&);
    DeclaratorExpr& operator=(const DeclaratorExpr&);
    DeclaratorExpr& operator=(const DeclaratorExpr&&);

    DeclaratorExpr(Token* tok, Token* = nullptr, Token* = nullptr, TerminalExpr* = nullptr, PointerExpr* = nullptr);
    DeclaratorExpr(Token* tok, Token* = nullptr, Token* = nullptr, ListExpr* = nullptr, PointerExpr* = nullptr);

    protected:
    virtual DeclaratorExpr* clone() const override { return new DeclaratorExpr(*this); }
    Token* name;
    union
    {
        Token* const_arg;
        ListExpr* arg_list;
        ParamListExpr* param_list;
    };
    PointerExpr* ptr;
    enum { EMPTY, CONSTARG, ARGLIST, PARAMLIST } arg_type;
    enum { BRACES, BRACKETS, PARENS, ANGLES } enclosure_type;
};

struct BlockExpr : Expr
{
    BlockExpr(const BlockExpr&);
    BlockExpr(const BlockExpr&&);
    BlockExpr& operator=(const BlockExpr&);
    BlockExpr& operator=(const BlockExpr&&);

    protected:
    Expr** exprs;
};


struct FlowControl : Expr
{
    FlowControl(const FlowControl&);
    FlowControl(const FlowControl&&);
    FlowControl& operator=(const FlowControl&);
    FlowControl& operator=(const FlowControl&&);
    BlockExpr* body;
};


struct Loop : Expr
{
    Loop(const Loop&);
    Loop(const Loop&&);
    Loop& operator=(const Loop&);
    Loop& operator=(const Loop&&);

    protected:
    Expr* before;
    Expr* condition;
    Expr* each;
};


struct IfElse : Expr
{
    IfElse(const IfElse&);
    IfElse(const IfElse&&);
    IfElse& operator=(const IfElse&);
    IfElse& operator=(const IfElse&&);

    protected:
    Expr* condition;
    Expr* else_body;
};
