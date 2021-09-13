#pragma once

#include <memory>
#include <vector>
#include <cstddef>
#include <string>

#include "token.hpp"


enum expr_id_t : unsigned char
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
    FLOW_CTRL,
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
    virtual expr_id_t id() const { return EXPR; };

    explicit Expr(struct Token*);

    virtual ~Expr();
    Expr(const Expr&);
    Expr(Expr&&);
    Expr& operator=(const Expr&);
    Expr& operator=(Expr&&);

    Expr() = delete;

    struct Token* get_token() const { return token; }

protected:
    virtual Expr* clone() const { return new Expr(*this); }
    struct Token* token;
};


struct NonTerminalExpr : Expr
{
    virtual expr_id_t id() const override { return NONTERMINAL; };

protected:
    virtual NonTerminalExpr* clone() const override { return new NonTerminalExpr(*this); }

    NonTerminalExpr(const NonTerminalExpr& other) : Expr(other) { };
    NonTerminalExpr(NonTerminalExpr&& other) : Expr(other) { };

    NonTerminalExpr(struct Token* tok) : Expr(tok) { };
};


struct TerminalExpr : NonTerminalExpr
{
    virtual expr_id_t id() const override { return TERMINAL; };

protected:
    virtual TerminalExpr* clone() const override { return new TerminalExpr(*this); }

    TerminalExpr(const TerminalExpr& other) : NonTerminalExpr(other) { };
    TerminalExpr(TerminalExpr&& other) : NonTerminalExpr(other) { };

    TerminalExpr(struct Token* tok) : NonTerminalExpr(tok) { };
};


struct BinaryExpr final : NonTerminalExpr
{
    virtual expr_id_t id() const override { return BINARY; };

    virtual ~BinaryExpr() override;
    BinaryExpr(const BinaryExpr&);
    BinaryExpr(BinaryExpr&&);
    BinaryExpr& operator=(const BinaryExpr&);
    BinaryExpr& operator=(BinaryExpr&&);

    BinaryExpr(struct Token*, NonTerminalExpr* = nullptr, NonTerminalExpr* = nullptr);

    NonTerminalExpr* get_left() const { return left; }
    NonTerminalExpr* get_right() const { return right; }

protected:
    virtual BinaryExpr* clone() const override { return new BinaryExpr(*this); }
    NonTerminalExpr* left;
    NonTerminalExpr* right;
};


struct UnaryExpr final : NonTerminalExpr
{
    virtual expr_id_t id() const override { return UNARY; };

    virtual ~UnaryExpr() override;
    UnaryExpr(const UnaryExpr&);
    UnaryExpr(UnaryExpr&&);
    UnaryExpr& operator=(const UnaryExpr&);
    UnaryExpr& operator=(UnaryExpr&&);

    UnaryExpr(struct Token*, NonTerminalExpr* = nullptr);

    NonTerminalExpr* get_operand() const { return operand; }

protected:
    virtual UnaryExpr* clone() const override { return new UnaryExpr(*this); }
    NonTerminalExpr* operand;
};


struct ListExpr : NonTerminalExpr
{
    virtual expr_id_t id() const override { return LIST; };

    virtual ~ListExpr() override;
    ListExpr(const ListExpr&);
    ListExpr(ListExpr&&);
    ListExpr& operator=(const ListExpr&);
    ListExpr& operator=(ListExpr&&);

    ListExpr(struct Token*, ListExpr* = nullptr);

    ListExpr* get_next() const { return next; }

protected:
    virtual ListExpr* clone() const override { return new ListExpr(*this); }
    ListExpr* next;
};


struct TypeExpr : Expr
{
    virtual expr_id_t id() const override { return TYPE; };

    TypeExpr(const TypeExpr&);
    TypeExpr(TypeExpr&&);
    TypeExpr& operator=(const TypeExpr&);
    TypeExpr& operator=(TypeExpr&&);

protected:
    virtual TypeExpr* clone() const override { return new TypeExpr(*this); }

    TerminalExpr* name;
};


struct ParamListExpr final : ListExpr
{
    virtual expr_id_t id() const override { return PARAM_LIST; };

    virtual ~ParamListExpr() override;
    ParamListExpr(const ParamListExpr&);
    ParamListExpr(ParamListExpr&&);
    ParamListExpr& operator=(const ParamListExpr&);
    ParamListExpr& operator=(ParamListExpr&&);

    ParamListExpr(struct Token*, TypeExpr*, TerminalExpr* = nullptr, ParamListExpr* = nullptr);

    TypeExpr* get_type() const { return type; }
    TerminalExpr* get_name() const { return name; }

protected:
    virtual ParamListExpr* clone() const override { return new ParamListExpr(*this); }
    TypeExpr* type;
    TerminalExpr* name;
};


struct PointerExpr final : NonTerminalExpr
{
    virtual expr_id_t id() const override { return POINTER; };

    virtual ~PointerExpr() override;
    PointerExpr(const PointerExpr&);
    PointerExpr(PointerExpr&&);
    PointerExpr& operator=(const PointerExpr&);
    PointerExpr& operator=(PointerExpr&&);

    PointerExpr(struct Token*, PointerExpr* = nullptr);

protected:
    virtual PointerExpr* clone() const override { return new PointerExpr(*this); }
    PointerExpr* ptr;
};


struct DeclaratorExpr final : NonTerminalExpr
{
    virtual expr_id_t id() const override { return DECLARATOR; };

    virtual ~DeclaratorExpr() override;
    DeclaratorExpr(const DeclaratorExpr&);
    DeclaratorExpr(DeclaratorExpr&&);
    DeclaratorExpr& operator=(const DeclaratorExpr&);
    DeclaratorExpr& operator=(DeclaratorExpr&&);

    DeclaratorExpr(struct Token* tok, struct Token* = nullptr, struct Token* = nullptr, TerminalExpr* = nullptr, PointerExpr* = nullptr);
    DeclaratorExpr(struct Token* tok, struct Token* = nullptr, struct Token* = nullptr, ListExpr* = nullptr, PointerExpr* = nullptr);

protected:
    virtual DeclaratorExpr* clone() const override { return new DeclaratorExpr(*this); }
    union
    {
        TerminalExpr* const_arg;
        ListExpr* arg_list;
        ParamListExpr* param_list;
    };
    PointerExpr* ptr;
    enum { EMPTY, CONSTARG, ARGLIST, PARAMLIST } arg_type;
    enum { BRACES, BRACKETS, PARENS, ANGLES } enclosure_type;
};


struct TypeExpr : Expr
{
    virtual expr_id_t id() const override { return TYPE; };

    TypeExpr(const TypeExpr&);
    TypeExpr(TypeExpr&&);
    TypeExpr& operator=(const TypeExpr&);
    TypeExpr& operator=(TypeExpr&&);

protected:
    virtual TypeExpr* clone() const override { return new TypeExpr(*this); }

    TerminalExpr* name;
};


struct BlockExpr : Expr
{
    virtual expr_id_t id() const override { return BLOCK; };

    BlockExpr(const BlockExpr&);
    BlockExpr(BlockExpr&&);
    BlockExpr& operator=(const BlockExpr&);
    BlockExpr& operator=(BlockExpr&&);

    BlockExpr() = default;

    void operator<<(Expr*);

protected:
    virtual BlockExpr* clone() const override { return new BlockExpr(*this); }

    std::vector<std::shared_ptr<Expr>> exprs;
};


struct FlowControlExpr : Expr
{
    virtual expr_id_t id() const override { return FLOW_CTRL; };

    FlowControlExpr(const FlowControlExpr&);
    FlowControlExpr(FlowControlExpr&&);
    FlowControlExpr& operator=(const FlowControlExpr&);
    FlowControlExpr& operator=(FlowControlExpr&&);

protected:
    virtual FlowControlExpr* clone() const override { return new FlowControlExpr(*this); }

    BlockExpr* body;
};


struct LoopExpr : Expr
{
    virtual expr_id_t id() const override { return LOOP; };

    LoopExpr(const LoopExpr&);
    LoopExpr(LoopExpr&&);
    LoopExpr& operator=(const LoopExpr&);
    LoopExpr& operator=(LoopExpr&&);

protected:
    virtual LoopExpr* clone() const override { return new LoopExpr(*this); }

    NonTerminalExpr* before;
    NonTerminalExpr* condition;
    NonTerminalExpr* each;
};


struct IfElseExpr : Expr
{
    virtual expr_id_t id() const override { return IF_ELSE; };

    IfElseExpr(const IfElseExpr&);
    IfElseExpr(IfElseExpr&&);
    IfElseExpr& operator=(const IfElseExpr&);
    IfElseExpr& operator=(IfElseExpr&&);

protected:
    virtual IfElseExpr* clone() const override { return new IfElseExpr(*this); }

    Expr* condition;
    Expr* else_body;
};


struct FuncDeclExpr : Expr
{
    virtual expr_id_t id() const override { return FUNCTION_DECLARATION; };

    FuncDeclExpr(const FuncDeclExpr&);
    FuncDeclExpr(FuncDeclExpr&&);
    FuncDeclExpr& operator=(const FuncDeclExpr&);
    FuncDeclExpr& operator=(FuncDeclExpr&&);

    std::int16_t get_signature() const;

protected:
    virtual FuncDeclExpr* clone() const override { return new FuncDeclExpr(*this); }

    DeclaratorExpr* declarator;
    TypeExpr* return_type;
};


struct VarDeclExpr : Expr
{
    virtual expr_id_t id() const override { return VAR_DECLARATION; };

    VarDeclExpr(const VarDeclExpr&);
    VarDeclExpr(VarDeclExpr&&);
    VarDeclExpr& operator=(const VarDeclExpr&);
    VarDeclExpr& operator=(VarDeclExpr&&);

protected:
    virtual VarDeclExpr* clone() const override { return new VarDeclExpr(*this); }

    TypeExpr* type;
    DeclaratorExpr* declarator;
};


struct MemberDeclExpr : Expr
{
    virtual expr_id_t id() const override { return STRUCT_MEMBER; };

protected:
    virtual MemberDeclExpr* clone() const override { return new MemberDeclExpr(*this); }

    bool _private;
    VarDeclExpr* var;
};


struct StructDefExpr : Expr
{
    virtual expr_id_t id() const override { return STRUCT_DEF; };

    StructDefExpr(const StructDefExpr&);
    StructDefExpr(StructDefExpr&&);
    StructDefExpr& operator=(const StructDefExpr&);
    StructDefExpr& operator=(StructDefExpr&&);

protected:
    virtual StructDefExpr* clone() const override { return new StructDefExpr(*this); }

    TypeExpr* type;
    std::vector<std::shared_ptr<MemberDeclExpr>> members;
};
