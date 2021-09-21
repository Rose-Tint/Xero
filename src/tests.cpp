#include <typeinfo>
#include <map>
#include <time.h>
#include <string>
#include "tests.hpp"

static std::string ttos(const Token& t)
{
    switch (t)
    {
        case EXIT:   return "EXIT";
        case ENTRY:  return "ENTRY";
        case NUM:    return "NUM";
        case ID:     return "ID";
        case EMPTY:  return "EMPTY";
        case LPAREN: return "LPAREN";
        case RPAREN: return "RPAREN";
        case NOT:    return "NOT";
        case AND:    return "AND";
        case OR:     return "OR";
        case XOR:    return "XOR";
        case EQ:     return "EQ";
        case GT:     return "GT";
        case LT:     return "LT";
        case MOD:    return "MOD";
        case DIV:    return "DIV";
        case MUL:    return "MUL";
        case PLUS:   return "PLUS";
        case MINUS:  return "MINUS";
        case ASN:    return "ASN";
        case LBRACE: return "LBRACE";
        case RBRACE: return "RBRACE";
        case ENDL:   return "ENDL";
    }
}

namespace tst
{
    ExprPtrTest::ExprPtrTest(Token token)
    {
        switch (token)
        {
            case ID:
            case NUM:
                ref = ExprPtr(token, "id_or_num");
                break;
            default:
                ref = ExprPtr(token);
        }
    }

    template<exp_behavior eb, class E>
    bool ExprPtrTest::test_add(Token fl_tok, Token fr_tok, Token sl_tok) const
    {
        fprintf(out, "add(%s, %s, %s): ", ttos(fl_tok), ttos(fr_tok), ttos(sl_tok));
        bool pass = false;
        ExprPtr root = ref;
        ExprPtr exp_fl;
        ExprPtr exp_fr;
        ExprPtr exp_sl;

        asn(exp_fl, fl_tok, "fl");
        asn(exp_fr, fr_tok, "fr");
        asn(exp_sl, sl_tok, "sl");

        try
        {
            root.add(exp_fl);
            root.add(exp_fr);
            root.add(exp_sl);

            if (eb == EQUATE)
            {
                pass &= (root.left().token() == exp_fl.token());
                pass &= (root.right().token() == exp_fr.token());
                pass &= (root.left().left().token() == exp_sl.token());
                out << (pass) ? "PASS" : "FAIL";
                return pass;
            }
            out << "FAIL";
            return false;
        }
        catch(E)
        {
            out << (eb == THROW) ? "PASS" : "FAIL";
            return eb == THROW;
        }
    }

    template<exp_behavior eb, class E>
    bool ExprPtrTest::test_unary(Token op_tok, Token operand_tok) const
    {
        fprintf(out, "unary(%s).add(%s): ", ttos(op_tok), ttos(operand_tok));
        bool pass = false;
        ExprPtr op = ExprPtr::unary(op_tok);
        ExprPtr exp_operand;

        asn(exp_operand, operand_tok, "operator");

        try
        {
            exp_operator.add(exp_operand);
            if (eb == EQUATE)
            {
                pass &= (op.left().token() == operand_tok);
                pass &= (op.right().token() == EMPTY);
                out << (pass) ? "PASS" : "FAIL";
                return pass;
            }
            out << "FAIL";
            return false;
        }
        catch(E)
        {
            out << (eb == THROW) ? "PASS" : "FAIL";
            return eb == THROW;
        }
    }

    bool ExprPtrTest::operator()(int& indent)
    {
        bool pass = false;
        std::string indent_s(indent + 1, '\t');
        out << std::string(indent, '\t') << "ExprPtr Tests:" << std::endl << indent_s;

        pass &= test_add<EQUATE>           (ASN  , ID  , NUM   ); out<<std::endl<<indent_s;
        pass &= test_add<EQUATE>           (PLUS , NUM , NUM   ); out<<std::endl<<indent_s;
        pass &= test_add<EQUATE>           (MOD  , PLUS, ID    ); out<<std::endl<<indent_s;
        pass &= test_add<EQUATE>           (DIV  , EQ  , MUL   ); out<<std::endl<<indent_s;
        pass &= test_add<EQUATE>           (LT   , ID  , GT    ); out<<std::endl<<indent_s;
        pass &= test_add<THROW, ExprError> (EMPTY, NUM , ID    ); out<<std::endl<<indent_s;
        pass &= test_add<THROW, ExprError> (ID   , NUM , PLUS  ); out<<std::endl<<indent_s;
        pass &= test_add<THROW, ExprError> (EXIT , DIV , _XOR  ); out<<std::endl<<indent_s;
        pass &= test_add<THROW, ExprError> (NUM  , NUM , NUM   ); out<<std::endl<<indent_s;
        pass &= test_add<THROW, ExprError> (ENDL , _AND, LBRACE); out<<std::endl<<indent_s;

        pass &= test_unary<EQUATE>(MINUS, NUM); out<<std::endl<<indent_s;

        return pass;
    }
}
