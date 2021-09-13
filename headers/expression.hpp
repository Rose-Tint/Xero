#pragma once

#include "type.hpp"
#include "scope.hpp"
#include "token.hpp"


typedef unsigned char id_t;


struct Expr
{
    virtual constexpr id_t id() const;

    explicit Expr(Token*);

    virtual ~Expr();
    Expr(const Expr&);
    Expr(const Expr&&);
    Expr& operator=(const Expr&);
    Expr& operator=(const Expr&&);

    Expr() = delete;

    Token* get_token () const;

    protected:

    Token* token;
};


struct NonTerminalExpr : Expr
{
    constexpr id_t id() const override;

    virtual ~NonTerminalExpr() override;
    NonTerminalExpr(const NonTerminalExpr&);
    NonTerminalExpr(const NonTerminalExpr&&);
    NonTerminalExpr& operator=(const NonTerminalExpr&);
    NonTerminalExpr& operator=(const NonTerminalExpr&&);
};


struct TerminalExpr : NonTerminalExpr
{
    constexpr id_t id() const override;

    virtual ~TerminalExpr() override;
    TerminalExpr(const TerminalExpr&);
    TerminalExpr(const TerminalExpr&&);
    TerminalExpr& operator=(const TerminalExpr&);
    TerminalExpr& operator=(const TerminalExpr&&);
};


struct ConstExpr : TerminalExpr
{
    constexpr id_t id() const override;

    virtual ~ConstExpr() override;
    ConstExpr(const ConstExpr&);
    ConstExpr(const ConstExpr&&);
    ConstExpr& operator=(const ConstExpr&);
    ConstExpr& operator=(const ConstExpr&&);
};


struct IdentifierExpr : TerminalExpr
{
    constexpr id_t id() const override;

    virtual ~IdentifierExpr() override;
    IdentifierExpr(const IdentifierExpr&);
    IdentifierExpr(const IdentifierExpr&&);
    IdentifierExpr& operator=(const IdentifierExpr&);
    IdentifierExpr& operator=(const IdentifierExpr&&);
};


struct LiteralExpr : ConstExpr
{
    constexpr id_t id() const override;

    virtual ~LiteralExpr() override;
    LiteralExpr(const LiteralExpr&);
    LiteralExpr(const LiteralExpr&&);
    LiteralExpr& operator=(const LiteralExpr&);
    LiteralExpr& operator=(const LiteralExpr&&);
};


struct BinaryOperationExpr : NonTerminalExpr
{
    constexpr id_t id() const override;

    virtual ~BinaryOperationExpr() override;
    BinaryOperationExpr(const BinaryOperationExpr&);
    BinaryOperationExpr(const BinaryOperationExpr&&);
    BinaryOperationExpr& operator=(const BinaryOperationExpr&);
    BinaryOperationExpr& operator=(const BinaryOperationExpr&&);

    BinaryOperationExpr(Token*, NonTerminalExpr* = nullptr, NonTerminalExpr* = nullptr);

    NonTerminalExpr* get_left() const;
    NonTerminalExpr* get_right() const;

    protected:
    NonTerminalExpr* left;
    NonTerminalExpr* right;
};


struct UnaryOperationExpr : NonTerminalExpr
{
    constexpr id_t id() const override;

    virtual ~UnaryOperationExpr() override;
    UnaryOperationExpr(const UnaryOperationExpr&);
    UnaryOperationExpr(const UnaryOperationExpr&&);
    UnaryOperationExpr& operator=(const UnaryOperationExpr&);
    UnaryOperationExpr& operator=(const UnaryOperationExpr&&);

    UnaryOperationExpr(Token*, Expr* = nullptr, Expr* = nullptr);

    Expr* get_operand() const;

    protected:
    Expr* operand;
};


struct ListExpr : NonTerminalExpr
{
    constexpr id_t id() const override;

    virtual ~ListExpr() override;
    ListExpr(const ListExpr&);
    ListExpr(const ListExpr&&);
    ListExpr& operator=(const ListExpr&);
    ListExpr& operator=(const ListExpr&&);

    ListExpr(Token*, ListExpr* = nullptr);

    ListExpr* get_next() const;

    protected:
    ListExpr* next;
};


struct ParamListExpr final : ListExpr
{
    constexpr id_t id() const override;

    virtual ~ParamListExpr() override;
    ParamListExpr(const ParamListExpr&);
    ParamListExpr(const ParamListExpr&&);
    ParamListExpr& operator=(const ParamListExpr&);
    ParamListExpr& operator=(const ParamListExpr&&);

    ParamListExpr(Token*, Type*, IdentifierExpr* = nullptr, ParamListExpr* = nullptr);


    protected:
    Type* type;
    IdentifierExpr* identifier;
    ParamListExpr* next;
};


struct ArgListExpr final : ListExpr
{
    constexpr id_t id() const override;

    virtual ~ArgListExpr() override;
    ArgListExpr(const ArgListExpr&);
    ArgListExpr(const ArgListExpr&&);
    ArgListExpr& operator=(const ArgListExpr&);
    ArgListExpr& operator=(const ArgListExpr&&);

    ArgListExpr(Token*, ArgListExpr* = nullptr);

    ArgListExpr* get_next() const;

    protected:
    IdentifierExpr* identifier;
    ArgListExpr* next;
};


struct PointerExpr final : Expr
{
    constexpr id_t id() const override;

    virtual ~PointerExpr() override;
    PointerExpr(const PointerExpr&);
    PointerExpr(const PointerExpr&&);
    PointerExpr& operator=(PointerExpr&);
    PointerExpr& operator=(PointerExpr&&);

    PointerExpr(Token*, Token*);

    PointerExpr* ptr;
};


struct DirectDeclaratorExpr : Expr
{
    constexpr id_t id() const override;

    virtual ~DirectDeclaratorExpr() override;
    DirectDeclaratorExpr(const DirectDeclaratorExpr&);
    DirectDeclaratorExpr(const DirectDeclaratorExpr&&);
    DirectDeclaratorExpr& operator=(const DirectDeclaratorExpr&);
    DirectDeclaratorExpr& operator=(const DirectDeclaratorExpr&&);

    DirectDeclaratorExpr(Token*, Token*, ConstExpr*);
    DirectDeclaratorExpr(Token*, Token*, ArgListExpr*);
    DirectDeclaratorExpr(Token*, Token*, ParamListExpr*);

    protected:
    DirectDeclaratorExpr* dir_declr;
    union
    {
        ConstExpr* const_arg;
        ArgListExpr* arg_list;
        ParamListExpr* param_list;
    };
    
};


struct DeclaratorExpr : DirectDeclaratorExpr
{
    constexpr id_t id() const override;

    virtual ~DeclaratorExpr() override;
    DeclaratorExpr(const DeclaratorExpr&);
    DeclaratorExpr(const DeclaratorExpr&&);
    DeclaratorExpr& operator=(const DeclaratorExpr&);
    DeclaratorExpr& operator=(const DeclaratorExpr&&);

    DeclaratorExpr(Token*, Token*, ConstExpr*);

    protected:
    PointerExpr* ptr;
};

