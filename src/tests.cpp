#include <typeinfo>
#include <map>
#include <time.h>
#include "tests.hpp"
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
                pass &= (root.left() == exp_fl);
                pass &= (root.right() == exp_fr);
                pass &= (root.left().left() == exp_fl);
            }
            else return false;
        }
        catch(E)
        {
            return eb == THROW;
        }
    }
}
