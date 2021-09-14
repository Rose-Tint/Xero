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
    STATEMENT,
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
    virtual void add(const Token*); // determines how to add an Expr* depending on both of the id() call
    virtual constexpr bool is_terminal() const = 0;
    virtual bool terminates() const = 0;
    virtual Expr* get_lowest_free() const = 0;

    explicit Expr(const Token*);
    virtual ~Expr();
    Expr(const Expr&);
    Expr(Expr&&);
    Expr& operator=(const Expr&);
    Expr& operator=(Expr&&);

    protected:
    virtual Expr* clone() const { return new Expr(*this); }
    Token* token = nullptr;
};


struct NonTerminalExpr : Expr
{
    virtual expr_id_t id() const override { return NONTERMINAL; };
    virtual void add(const Token*) = 0;
    virtual constexpr bool is_terminal() const override { return false; }
    virtual bool terminates() const = 0;
    virtual NonTerminalExpr* get_lowest_free() const = 0;

    protected:
    virtual NonTerminalExpr* clone() const override { return new NonTerminalExpr(*this); }

    NonTerminalExpr(const NonTerminalExpr& other) : Expr(other) { };
    NonTerminalExpr(NonTerminalExpr&& other) : Expr(other) { };
    NonTerminalExpr& operator=(const NonTerminalExpr&);
    NonTerminalExpr& operator=(NonTerminalExpr&&);

    explicit NonTerminalExpr(Token* tok) : Expr(tok) { };
};


struct TerminalExpr final : virtual NonTerminalExpr
{
    virtual expr_id_t id() const override { return TERMINAL; };
    virtual void add(const Token*) = 0;
    virtual constexpr bool is_terminal() const final override { return true; }
    virtual bool terminates() const override;
    virtual NonTerminalExpr* get_lowest_free() const = 0;

    explicit TerminalExpr(Token* tok) : NonTerminalExpr(tok) { }
    TerminalExpr(const TerminalExpr& other) : NonTerminalExpr(other) { };
    TerminalExpr(TerminalExpr&& other) :  NonTerminalExpr(other) { };
    TerminalExpr& operator=(const TerminalExpr&);
    TerminalExpr& operator=(TerminalExpr&&);

    protected:
    virtual TerminalExpr* clone() const override { return new TerminalExpr(*this); }

};


struct BinaryExpr final : virtual NonTerminalExpr
{
    virtual expr_id_t id() const override { return BINARY; };
    virtual void add(const Token*) override;
    virtual bool terminates() const override;
    virtual NonTerminalExpr* get_lowest_free() const override;

    explicit BinaryExpr(Token* tok) : NonTerminalExpr(tok) {}
    virtual ~BinaryExpr() override;
    BinaryExpr(const BinaryExpr&);
    BinaryExpr(BinaryExpr&&);
    BinaryExpr& operator=(const BinaryExpr&);
    BinaryExpr& operator=(BinaryExpr&&);


    protected:
    virtual BinaryExpr* clone() const override { return new BinaryExpr(*this); }
    NonTerminalExpr* left = nullptr;
    NonTerminalExpr* right = nullptr;
};


struct UnaryExpr final : virtual NonTerminalExpr
{
    virtual expr_id_t id() const override { return UNARY; };
    virtual void add(const Token*) override;
    virtual bool terminates() const override;
    virtual NonTerminalExpr* get_lowest_free() const override;

    explicit UnaryExpr(Token* tok) : NonTerminalExpr(tok) {}
    virtual ~UnaryExpr() override;
    UnaryExpr(const UnaryExpr&);
    UnaryExpr(UnaryExpr&&);
    UnaryExpr& operator=(const UnaryExpr&);
    UnaryExpr& operator=(UnaryExpr&&);

    protected:
    virtual UnaryExpr* clone() const override { return new UnaryExpr(*this); }
    NonTerminalExpr* operand = nullptr;
};


struct ListExpr : virtual NonTerminalExpr
{
    virtual expr_id_t id() const override { return LIST; };
    virtual void add(const Token*) = 0;
    virtual bool terminates() const = 0;
    virtual NonTerminalExpr* get_lowest_free() const override;

    explicit ListExpr(Token* tok) : NonTerminalExpr(tok) {}
    virtual ~ListExpr() override;
    ListExpr(const ListExpr&);
    ListExpr(ListExpr&&);
    ListExpr& operator=(const ListExpr&);
    ListExpr& operator=(ListExpr&&);

    protected:
    virtual ListExpr* clone() const override { return new ListExpr(*this); }
    NonTerminalExpr* arg = nullptr;
    ListExpr* next = nullptr;
};


struct PointerExpr final : virtual NonTerminalExpr
{
    virtual expr_id_t id() const override { return POINTER; };
    virtual void add(const Token*) override;
    virtual bool terminates() const override;
    virtual NonTerminalExpr* get_lowest_free() const override;

    explicit PointerExpr(Token* tok) : NonTerminalExpr(tok) {}
    virtual ~PointerExpr() override;
    PointerExpr(const PointerExpr&);
    PointerExpr(PointerExpr&&);
    PointerExpr& operator=(const PointerExpr&);
    PointerExpr& operator=(PointerExpr&&);

    protected:
    virtual PointerExpr* clone() const override { return new PointerExpr(*this); }
    PointerExpr* ptr = nullptr;
};


struct TypeExpr final : virtual NonTerminalExpr
{
    virtual expr_id_t id() const override { return TYPE; };
    virtual void add(const Token*) override;
    virtual bool terminates() const override;
    virtual NonTerminalExpr* get_lowest_free() const override;

    explicit TypeExpr(Token* tok) : NonTerminalExpr(tok) {}
    TypeExpr(const TypeExpr&);
    TypeExpr(TypeExpr&&);
    TypeExpr& operator=(const TypeExpr&);
    TypeExpr& operator=(TypeExpr&&);

    protected:
    virtual TypeExpr* clone() const override { return new TypeExpr(*this); }
    TerminalExpr* name = nullptr;
    PointerExpr* ptr = nullptr;
};


struct DeclaratorExpr final : virtual NonTerminalExpr
{
    virtual expr_id_t id() const override { return DECLARATOR; };
    virtual void add(const Token*) override;
    virtual bool terminates() const override;
    virtual NonTerminalExpr* get_lowest_free() const override;

    explicit DeclaratorExpr(Token* tok) : NonTerminalExpr(tok) {}
    virtual ~DeclaratorExpr() override;
    DeclaratorExpr(const DeclaratorExpr&);
    DeclaratorExpr(DeclaratorExpr&&);
    DeclaratorExpr& operator=(const DeclaratorExpr&);
    DeclaratorExpr& operator=(DeclaratorExpr&&);

    protected:
    virtual DeclaratorExpr* clone() const override { return new DeclaratorExpr(*this); }
    TerminalExpr* name = nullptr;
    DeclaratorExpr* declarator = nullptr;
    union
    {
        TerminalExpr* const_arg = nullptr;
        ListExpr* list = nullptr;
    };
    PointerExpr* ptr = nullptr;
    enum { EMPTY, CONSTARG, ARGLIST, PARAMLIST } arg_type;
    enum { BRACES, BRACKETS, PARENS, ANGLES } enclosure_type;
};


struct StatementExpr : Expr
{
    virtual expr_id_t id() const override { return STATEMENT; };
    virtual void add(const Token*) override;
    virtual bool terminates() const override;
    virtual NonTerminalExpr* get_lowest_free() const override;

    explicit StatementExpr(Token* tok) : Expr(tok) {}
    StatementExpr(const StatementExpr&);
    StatementExpr(StatementExpr&&);
    StatementExpr& operator=(const StatementExpr&);
    StatementExpr& operator=(StatementExpr&&);

    protected:
    virtual StatementExpr* clone() const override { return new StatementExpr(*this); }

    std::vector<NonTerminalExpr*> exprs;
};


struct BlockExpr : Expr
{
    virtual expr_id_t id() const override { return BLOCK; };
    virtual void add(const Token*) override;
    virtual bool terminates() const override;
    virtual NonTerminalExpr* get_lowest_free() const override;

    explicit BlockExpr(const Token* tok) : Expr(tok) {}
    BlockExpr(const BlockExpr&);
    BlockExpr(BlockExpr&&);
    BlockExpr& operator=(const BlockExpr&);
    BlockExpr& operator=(BlockExpr&&);

    const std::vector<StatementExpr*>& get_exprs() const;

    protected:
    virtual BlockExpr* clone() const override { return new BlockExpr(*this); }

    std::vector<StatementExpr*> exprs;
};


struct FlowControlExpr : Expr
{
    virtual expr_id_t id() const override { return FLOW_CTRL; };
    virtual void add(const Token*) override;
    virtual bool terminates() const override;
    virtual NonTerminalExpr* get_lowest_free() const override;

    FlowControlExpr(const FlowControlExpr&);
    FlowControlExpr(FlowControlExpr&&);
    FlowControlExpr& operator=(const FlowControlExpr&);
    FlowControlExpr& operator=(FlowControlExpr&&);

    protected:
    virtual FlowControlExpr* clone() const override { return new FlowControlExpr(*this); }

    BlockExpr* body = nullptr;
};


struct LoopExpr : FlowControlExpr
{
    virtual expr_id_t id() const override { return LOOP; };
    virtual void add(const Token*) override;
    virtual bool terminates() const override;
    virtual NonTerminalExpr* get_lowest_free() const override;

    LoopExpr(const LoopExpr&);
    LoopExpr(LoopExpr&&);
    LoopExpr& operator=(const LoopExpr&);
    LoopExpr& operator=(LoopExpr&&);

    protected:
    virtual LoopExpr* clone() const override { return new LoopExpr(*this); }

    NonTerminalExpr* before = nullptr;
    NonTerminalExpr* condition = nullptr;
    NonTerminalExpr* each = nullptr;
};


struct IfElseExpr : FlowControlExpr
{
    virtual expr_id_t id() const override { return IF_ELSE; };
    virtual void add(const Token*) override;
    virtual bool terminates() const override;
    virtual NonTerminalExpr* get_lowest_free() const override;

    IfElseExpr(const IfElseExpr&);
    IfElseExpr(IfElseExpr&&);
    IfElseExpr& operator=(const IfElseExpr&);
    IfElseExpr& operator=(IfElseExpr&&);

    protected:
    virtual IfElseExpr* clone() const override { return new IfElseExpr(*this); }

    Expr* condition = nullptr;
    bool has_else = nullptr;
    Expr* else_body = nullptr;
};


struct FuncDeclExpr : StatementExpr
{
    virtual expr_id_t id() const override { return FUNCTION_DECLARATION; };
    virtual void add(const Token*) override;
    virtual bool terminates() const override;
    virtual NonTerminalExpr* get_lowest_free() const override;

    FuncDeclExpr(const FuncDeclExpr&);
    FuncDeclExpr(FuncDeclExpr&&);
    FuncDeclExpr& operator=(const FuncDeclExpr&);
    FuncDeclExpr& operator=(FuncDeclExpr&&);

    std::int16_t get_signature() const;

    protected:
    virtual FuncDeclExpr* clone() const override { return new FuncDeclExpr(*this); }

    DeclaratorExpr* declarator = nullptr;
    TypeExpr* return_type = nullptr;
};


struct VarDeclExpr : NonTerminalExpr
{
    virtual expr_id_t id() const override { return VAR_DECLARATION; };
    virtual void add(const Token*) override;
    virtual bool terminates() const override;
    virtual NonTerminalExpr* get_lowest_free() const override;

    VarDeclExpr(const VarDeclExpr&);
    VarDeclExpr(VarDeclExpr&&);
    VarDeclExpr& operator=(const VarDeclExpr&);
    VarDeclExpr& operator=(VarDeclExpr&&);

    protected:
    virtual VarDeclExpr* clone() const override { return new VarDeclExpr(*this); }

    TypeExpr* type = nullptr;
    DeclaratorExpr* declarator = nullptr;
};


struct MemberDeclExpr : StatementExpr
{
    virtual expr_id_t id() const override { return STRUCT_MEMBER; };
    virtual void add(const Token*) override;
    virtual bool terminates() const override;
    virtual NonTerminalExpr* get_lowest_free() const override;

    protected:
    virtual MemberDeclExpr* clone() const override { return new MemberDeclExpr(*this); }

    VarDeclExpr* var = nullptr;
};


struct StructDefExpr : Expr
{
    virtual expr_id_t id() const override { return STRUCT_DEF; };
    virtual void add(const Token*) override;
    virtual bool terminates() const override;
    virtual NonTerminalExpr* get_lowest_free() const override;

    StructDefExpr(const StructDefExpr&);
    StructDefExpr(StructDefExpr&&);
    StructDefExpr& operator=(const StructDefExpr&);
    StructDefExpr& operator=(StructDefExpr&&);

    protected:
    virtual StructDefExpr* clone() const override { return new StructDefExpr(*this); }

    TypeExpr* type = nullptr;
    std::vector<std::shared_ptr<MemberDeclExpr>> members;
};


const BlockExpr& top_level_ref = BlockExpr(Token("TOP_LEVEL"));
