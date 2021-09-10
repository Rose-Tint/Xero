#pragma once

#include "token.hpp"


struct ExprBase
{
    token_t token;

    ExprBase(const ExprBase&) = default;
    virtual ~ExprBase() = default;
    explicit ExprBase(token_t) = default;

    bool is_finished() const;
    bool is_final() const;
};


struct TermExpr : public ExprBase
{
    ;
};


struct OpExpr : public ExprBase
{
    private:
    ExprBase* left;
    ExprBase* right;

    public:
    OpExpr(ExprBase*);
    OpExpr(ExprBase*, ExprBase*);
    ExprBase* get_left() const { return left; }
    ExprBase* get_right() const { return right; }
    ~OpExpr() override;
};



