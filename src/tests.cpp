#include <string>

#include "tests.hpp"
#include "error.hpp"

#define COUTDEBUG std::cout << "here " << std::endl;

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
        ref = ExprPtr();
        asn(ref, token);
    }

    void ExprPtrTest::asn(ExprPtr& e, Token t, std::string s)
    {
        switch (t)
        {
            case ID:
            case NUM:
                e = ExprPtr(t, s);
                return;
            default:
                e = ExprPtr(t);
                return;
        }
    }

    template<exp_behavior eb, class E>
    bool ExprPtrTest::test_add(Token fl_tok, Token fr_tok, Token sl_tok)
    {
        printf("add(%-6s, %-6s, %-6s): ", ttos(fl_tok).c_str(), ttos(fr_tok).c_str(), ttos(sl_tok).c_str());
        std::cout.flush();

        if (!is_terminal(sl_tok) && eb == EQUATE)
        {
            std::cout << "FAIL (invalid test arg (non terminating sl))";
            return false;
        }
        if (is_terminal(fl_tok) && eb == EQUATE)
        {
            std::cout << "FAIL (invalid test arg (terminating fl))";
            return false;
        }

        bool pass = false;
        ExprPtr root = ref;
        ExprPtr exp_fl;
        ExprPtr exp_fr;
        ExprPtr exp_sl;
        ExprPtr exp_sr;

        asn(exp_fl, fl_tok, "fl");
        asn(exp_fr, fr_tok, "fr");
        asn(exp_sl, sl_tok, "sl");
        asn(exp_sr, ID    , "sr");
 
        try
        {
            root.add(exp_fl);
            root.add(exp_fr);
            root.add(exp_sl);
            root.add(exp_sr);

            if (eb == EQUATE)
            {
                if (root.is_null())
                {
                    std::cout << "FAIL (root is null)";
                    return false;
                }
                else if (root.left().is_null())
                {
                    std::cout << "FAIL (left is null)";
                    return false;
                }
                else if (root.right().is_null())
                {
                    std::cout << "FAIL (right is null)";
                    return false;
                }
                else if (root.left().left().is_null())
                {
                    std::cout << "FAIL (left.left is null)";
                    return false;
                }
                else if (root.left().right().is_null())
                {
                    std::cout << "FAIL (left.right is null)";
                    return false;
                }
                pass &= (root.left().token() == exp_fl.token());
                pass &= (root.right().token() == exp_fr.token());
                pass &= (root.left().left().token() == exp_sl.token());
                pass &= (root.left().right().token() == ID);
                std::cout << ((pass) ? "PASS" : "FAIL (non-matching tokens)");
                return pass;
            }
            std::cout << "FAIL (expected error not thrown)";
            return false;
        }
        catch(E)
        {
            std::cout << ((eb == THROW) ? "PASS" : "FAIL (unexpected error thrown)");
            return eb == THROW;
        }
    }

    template<exp_behavior eb, class E>
    bool ExprPtrTest::test_unary(Token op_tok, Token operand_tok)
    {
        printf("unary(%s) -> add(%s):    ", ttos(op_tok).c_str(), ttos(operand_tok).c_str());
        bool pass = false;
        ExprPtr op = ExprPtr::unary(op_tok);
        ExprPtr exp_operand;

        asn(exp_operand, operand_tok, "operator");

        try
        {
            op.add(exp_operand);
            if (eb == EQUATE)
            {
                pass &= (op.left().token() == operand_tok);
                pass &= (op.right().token() == EMPTY);
                std::cout << ((pass) ? "PASS" : "FAIL (non-matching tokens)");
                return pass;
            }
            std::cout << "FAIL (expected error not thrown)";
            return false;
        }
        catch(E)
        {
            std::cout << ((eb == THROW) ? "PASS" : "FAIL (unexpected error thrown)");
            return eb == THROW;
        }
    }

    bool ExprPtrTest::operator()(int& indent)
    {
        bool pass = false;
        std::cout << "ExprPtr Tests:\n  non throwing" << std::endl << '\t';

        pass &= test_add <EQUATE> (ASN , ID  , NUM); std::cout << std::endl << '\t';
        pass &= test_add <EQUATE> (PLUS, NUM , NUM); std::cout << std::endl << '\t';
        pass &= test_add <EQUATE> (MOD , PLUS, ID ); std::cout << std::endl << '\t';
        pass &= test_add <EQUATE> (DIV , EQ  , NUM); std::cout << std::endl << '\t';
        pass &= test_add <EQUATE> (LT  , ID  , ID ); std::cout << std::endl << "  ";

        std::cout << "throwing" << std::endl << '\t';

        pass &= test_add <THROW> (EMPTY, NUM , ID    ); std::cout << std::endl << '\t';
        pass &= test_add <THROW> (ID   , NUM , PLUS  ); std::cout << std::endl << '\t';
        pass &= test_add <THROW> (EXIT , DIV , XOR   ); std::cout << std::endl << '\t';
        pass &= test_add <THROW> (NUM  , NUM , NUM   ); std::cout << std::endl << '\t';
        pass &= test_add <THROW> (ENDL , AND , LBRACE); std::cout << std::endl << '\t';

        pass &= test_unary<EQUATE>(MINUS, NUM); std::cout << std::endl << '\t';

        return pass;
    }
}
