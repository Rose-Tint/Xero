#pragma once

#include <memory>
#include <vector>
#include <cstddef>

#include "scope.hpp"
#include "token.hpp"


enum id_t : unsigned char
{
    EXPR,
    NONTERMINAL,
    TERMINAL,
    BINARY,
    UNARY,
    LIST,
    PARAM_LIST,
    POINTER,
    DECLARATOR,
    TYPE,
    BLOCK,
    LOOP,
    IF_ELSE,
    FUNCTION_DECLARATION,
    VAR_DECLARATION,
    STRUCT_MEMBER,
    STRUCT_DEF
};


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
    virtual Expr* clone() const override { return new Expr(*this); }
    Token* token;
    static Expr* safe_clone(const Expr* expr) { return (expr != nullptr) ? expr->clone() : nullptr; }
};


struct NonTerminalExpr : Expr
{
    virtual id_t id() const override { return NONTERMINAL; };

protected:
    virtual NonTerminalExpr* clone() const override { return new NonTerminalExpr(*this); }

    NonTerminalExpr(const NonTerminalExpr& other) : Expr(other) { }
    NonTerminalExpr(const NonTerminalExpr&& other) : Expr(other) { }

    NonTerminalExpr(Token* tok) : Expr(tok) { }
};


struct TerminalExpr : NonTerminalExpr
{
    virtual id_t id() const override { return TERMINAL; };

protected:
    virtual TerminalExpr* clone() const override { return new TerminalExpr(*this); }

    TerminalExpr(const TerminalExpr& other) : NonTerminalExpr(other) { }
    TerminalExpr(const TerminalExpr&& other) : NonTerminalExpr(other) { }

    TerminalExpr(Token* tok) : NonTerminalExpr(tok) { }
};


struct BinaryOperationExpr final : NonTerminalExpr
{
    virtual id_t id() const override { return BINARY; };

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
    virtual id_t id() const override { return UNARY; };

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
    virtual id_t id() const override { return LIST; };

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
    virtual id_t id() const override { return PARAM_LIST; };

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
    virtual id_t id() const override { return POINTER; };

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
    virtual id_t id() const override { return DECLARATOR; };

    virtual ~DeclaratorExpr() override;
    DeclaratorExpr(const DeclaratorExpr&);
    DeclaratorExpr(const DeclaratorExpr&&);
    DeclaratorExpr& operator=(const DeclaratorExpr&);
    DeclaratorExpr& operator=(const DeclaratorExpr&&);

    DeclaratorExpr(Token* tok, Token* = nullptr, Token* = nullptr, TerminalExpr* = nullptr, PointerExpr* = nullptr);
    DeclaratorExpr(Token* tok, Token* = nullptr, Token* = nullptr, ListExpr* = nullptr, PointerExpr* = nullptr);

protected:
    virtual DeclaratorExpr* clone() const override { return new DeclaratorExpr(*this); }
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


struct TypeExpr
{
    virtual id_t id() const override { return TYPE; };

    TypeExpr(const TypeExpr&);
    TypeExpr(const TypeExpr&&);
    TypeExpr& operator=(const TypeExpr&);
    TypeExpr& operator=(const TypeExpr&&);

protected:
    virtual TypeExpr* clone() const override { return new TypeExpr(*this); }

    TerminalExpr* name;
};


struct BlockExpr : Expr
{
    virtual id_t id() const override { return BLOCK; };

    BlockExpr(const BlockExpr&);
    BlockExpr(const BlockExpr&&);
    BlockExpr& operator=(const BlockExpr&);
    BlockExpr& operator=(const BlockExpr&&);

    BlockExpr() = default;

    void operator<<(Expr*);

protected:
    virtual BlockExpr* clone() const override { return new BlockExpr(*this); }

    std::vector<std::shared_ptr<Expr>> exprs;
};


struct FlowControlExpr : Expr
{
    virtual id_t id() const override { return FLOW_CTRL; };

    FlowControlExpr(const FlowControlExpr&);
    FlowControlExpr(const FlowControlExpr&&);
    FlowControlExpr& operator=(const FlowControlExpr&);
    FlowControlExpr& operator=(const FlowControlExpr&&);

protected:
    virtual FlowControlExpr* clone() const override { return new FlowControlExpr(*this); }

    BlockExpr* body;
};


struct LoopExpr : Expr
{
    virtual id_t id() const override { return LOOP; };

    LoopExpr(const LoopExpr&);
    LoopExpr(const LoopExpr&&);
    LoopExpr& operator=(const LoopExpr&);
    LoopExpr& operator=(const LoopExpr&&);

protected:
    virtual LoopExpr* clone() const override { return new LoopExpr(*this); }

    NonTerminalExpr* before;
    NonTerminalExpr* condition;
    NonTerminalExpr* each;
};


struct IfElseExpr : Expr
{
    virtual id_t id() const override { return IF_ELSE; };

    IfElseExpr(const IfElseExpr&);
    IfElseExpr(const IfElseExpr&&);
    IfElseExpr& operator=(const IfElseExpr&);
    IfElseExpr& operator=(const IfElseExpr&&);

protected:
    virtual IfElseExpr* clone() const override { return new IfElseExpr(*this); }

    Expr* condition;
    Expr* else_body;
};


struct FuncDeclExpr : Expr
{
    virtual id_t id() const override { return FUNCTION_DECLARATION; };

    FuncDeclExpr(const FuncDeclExpr&);
    FuncDeclExpr(const FuncDeclExpr&&);
    FuncDeclExpr& operator=(const FuncDeclExpr&);
    FuncDeclExpr& operator=(const FuncDeclExpr&&);

    std::int16_t get_signature() const;

protected:
    virtual FuncDeclExpr* clone() const override { return new FuncDeclExpr(*this); }

    DeclaratorExpr* declarator;
    TypeExpr* return_type;
};


struct VarDeclExpr : Expr
{
    virtual id_t id() const override { return VAR_DECLARATION; };

    VarDeclExpr(const VarDeclExpr&);
    VarDeclExpr(const VarDeclExpr&&);
    VarDeclExpr& operator=(const VarDeclExpr&);
    VarDeclExpr& operator=(const VarDeclExpr&&);

protected:
    virtual VarDeclExpr* clone() const override { return new VarDeclExpr(*this); }

    TypeExpr* type;
    DeclaratorExpr* declarator;
};


struct MemberDeclExpr
{
    virtual id_t id() const override { return STRUCT_MEMBER; };

protected:
    virtual MemberDeclExpr* clone() const override { return new MemberDeclExpr(*this); }

    bool _private;
    VarDeclExpr* var;
};


struct StructDefExpr
{
    virtual id_t id() const override { return STRUCT_DEF; };

    StructDef(const StructDef&);
    StructDef(const StructDef&&);
    StructDef& operator=(const StructDef&);
    StructDef& operator=(const StructDef&&);

protected:
    virtual StructDef* clone() const override { return new StructDef(*this); }

    TypeExpr* type;
    std::vector<std::shared_ptr<MemberDeclExpr>> members;
};
