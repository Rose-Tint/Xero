#include <string>
#include <stack>

#pragma GCC diagnostic ignored "-Wformat-security"

#include "../headers/tests.hpp"


namespace tst
{
    unsigned char TestBase::idt = 0;

    std::vector<std::streambuf*> TestBase::bstack { };
    std::vector<TestBase*> TestBase::tests { };

    bool TestBase::run_tests()
    {
        bool pass;
        for (auto test : tests)
        {
            pass &= test->run();
        }
        return pass;
    }

    void TestBase::reg(std::streambuf* buf)
    {
        bstack.push_back(buf);
    }

    void TestBase::print_stack(const std::string& str)
    {
        for (std::streambuf* buf : bstack)
        {
            std::iostream s(buf);
            s << str;
            s.flush();
        }
    }

    template<typename ...Args>
    void TestBase::print(std::string str, Args... args)
    {
        str.insert(0, idt, '\t');
        for (std::size_t j = 0, k = 0; (str.find("~", j + k)) < str.size(); k = 2)
        {
            j = str.find("~", j + k);
            k = 2;
            switch (str[j + 1])
            {
                case '+': idt++; break;
                case '-': idt--; break;
                case '~': break;
                default: k = 1;
            }
            str.replace(j, k, std::string(idt, '\t'));
        }
        int size_s = std::snprintf(nullptr, 0, str.c_str(), args...) + 1;
        auto size = static_cast<std::size_t>(size_s);
        auto cstr = new char[size];
        std::snprintf(cstr, size, str.c_str(), args...);
        str = std::string(cstr);
        print_stack(str);
    }

    template<typename>
    void TestBase::print(std::string str)
    {
        str.insert(0, idt, '\t');
        for (std::size_t j = 0, k = 0; (str.find("~", j + k)) < str.size(); k = 2)
        {
            j = str.find("~", j + k);
            k = 2;
            switch (str[j + 1])
            {
                case '+': idt++; break;
                case '-': idt--; break;
                case '~': break;
                default: k = 1;
            }
            str.replace(j, k, std::string(idt, '\t'));
        }
        print_stack(str);
    }

    ExprPtr ExprPtrTest::ref = ExprPtr(ENTRY);

    ExprPtr ExprPtrTest::asn(Token t, std::string s)
    {
        switch (t)
        {
            case ID:
            case NUM:
                return ExprPtr(t, s);
            default:
                return ExprPtr(t);
        }
    }

    template<exp_behavior eb, class E>
    bool ExprPtrTest::test_add(Token l_tok, Token r_tok, Token ll_tok)
    {
        print("add:\n~+input:\n~+left; %s\n~~right; %s\n~~left_left; %s\n", ttos(l_tok), ttos(r_tok), ttos(ll_tok));
        idt--;

        if (is_terminal(l_tok) && eb == EQUATE)
        {
            print("result; FAIL (invalid test arg (terminating _l))");
            idt -= 1;
            return false;
        }

        bool pass = true;
        ExprPtr root = ref;
        ExprPtr exp_l, exp_ll, exp_lll, exp_llr, exp_lr, exp_r;

        exp_l = asn(l_tok, "left");
        exp_ll = asn(ll_tok, "left_left");
        if (!is_terminal(ll_tok))
        {
            exp_lll = asn(NUM, "left_left_left");
            exp_llr = asn(NUM, "left_left_right");
        }
        exp_lr = asn(ID, "left_right");
        exp_r = asn(r_tok, "right");
 
        try
        {
            root.add(exp_l);
            root.add(exp_ll);
            if (!is_terminal(ll_tok))
            {
                root.add(exp_lll);
                root.add(exp_llr);
            }
            root.add(exp_lr);
            root.add(exp_r);

            if (eb == EQUATE)
            {
                {
                    bool ctns_null = false;
                    std::string f_expr_s;
                    if (root.is_null()) { ctns_null = true; f_expr_s = "root"; }
                    else if (root.left().is_null()) { ctns_null = true; f_expr_s = "rl"; }
                    else if (root.right().is_null()) { ctns_null = true; f_expr_s = "_r"; }
                    else if (root.left().left().is_null()) { ctns_null = true; f_expr_s = "ll"; }
                    else if (root.left().right().is_null()) { ctns_null = true; f_expr_s = "lr"; }
                    if (ctns_null)
                    {
                        print("result; FAIL (%s is null)", f_expr_s.c_str());
                        return false;
                    }
                }

                pass &= (root.left().token() == l_tok);
                if (!pass)
                {
                    idt--;
                    print("result; FAIL (wrong _l token):\n~+got: %s\n~~found: %s", ttos(root.left().token()), ttos(l_tok));
                    idt -= 1;
                    return false;
                }
                pass &= (root.right().token() == r_tok);
                if (!pass)
                {
                    idt--;
                    print("result; FAIL (wrong _r token):\n~+got: %s\n~~found: %s", ttos(root.right().token()), ttos(r_tok));
                    idt -= 1;
                    return false;
                }
                pass &= (root.left().left().token() == ll_tok);
                if (!pass)
                {
                    idt--;
                    print("result; FAIL (wrong ll token):\n~+got: %s\n~~found: %s", ttos(root.left().left().token()), ttos(ll_tok));
                    idt -= 1;
                    return false;
                }
                pass &= (root.left().right().token() == ID);
                if (!pass)
                {
                    idt--;
                    print("result; FAIL (wrong lr token):\n~+got: %s\n~~found: ID", ttos(root.left().right().token()));
                    idt -= 1;
                    return false;
                }
                else
                {
                    print("result; PASS");
                    idt -= 1;
                    return true;
                }
            }
            print("result; FAIL (error not thrown)");
            return false;
        }
        catch(E)
        {
            print("result; %s", (eb == THROW) ? "PASS" : "FAIL (unexpected error thrown)");
            idt -= 1;
            return eb == THROW;
        }
        catch(err::Error& e)
        {
            print("result; FAIL (unexpected error: %s)", typeid(e).name());
            return false;
        }
    }

    bool ExprPtrTest::run()
    {
        bool pass = false;
        auto old_idt = idt;
        print("ExprPtr Tests:\n~+non throwing:\n");
        idt++;

        pass &= test_add <EQUATE> (ASN , ID  , NUM  ); newl();
        pass &= test_add <EQUATE> (PLUS, NUM , XOR  ); newl();
        pass &= test_add <EQUATE> (MOD , PLUS, ID   ); newl();
        pass &= test_add <EQUATE> (DIV , EQ  , MUL  ); newl();
        pass &= test_add <EQUATE> (LT  , ID  , MINUS);

            print("\n~-throwing:\n"); idt++;
        pass &= test_add <THROW, err::ExprError>          (EMPTY, NUM , NUM); newl();
        pass &= test_add <THROW, err::UnaddableExprError> (ID   , NUM , ID ); newl();
        pass &= test_add <THROW, err::ExprError>          (EXIT , DIV , ID ); newl();
        pass &= test_add <THROW, err::UnaddableExprError> (NUM  , NUM , NUM); newl();
        pass &= test_add <THROW, err::ExprError>          (ENDL , AND , ID ); newl();

        idt = old_idt;
        return pass;
    }

    bool LexerTest::test_next(std::string str, std::vector<Token> tokens)
    {
        print("next:\n~+input:\n~+string; '%s'\n~~tokens;", str.c_str());
        for (Token t : tokens) print_stack(std::string(" ") + ttos(t));
        newl();
        print("finding:\n"); idt++;

        bool pass = true;
        std::stringstream ss = std::stringstream(str);
        try
        {
            Lexer lxr = Lexer(ss);
            for (Token t : tokens)
            {
                pass &= (lxr.next() == t);
                print("t: '%-8s', b: '%s'", ttos(lxr.get()), lxr.get_val().c_str());
                newl();
                if (!pass)
                {
                    idt -= 2;
                    print("result; FAIL:\n~+found;' %s'\n~~given; '%s'", ttos(lxr.get()), ttos(t));
                    idt -= 2;
                    return false;
                }
            }
            idt -= 2;
            print("result; PASS");
            idt -= 1;
            return true;
        }
        catch(err::LexerError e)
        {
            idt -= 2;
            print("result; FAIL (error thrown: %s)", e.what());
            idt -= 1;
            return false;
        }
    }

    bool LexerTest::run()
    {
        bool pass = true;
        auto old_idt = idt;
        print("Lexer Tests:\n");
        idt++;

        pass &= test_next("int i: 1 + 2"       , { ID, ID, ASN, NUM, PLUS, NUM, EXIT                }); newl();
        pass &= test_next("foo : n % (24)"     , { ID, ASN, ID, MOD, LPAREN, NUM, RPAREN, EXIT      }); newl();
        pass &= test_next("bar[17 ^ i]:"       , { ID, LBRACKET, NUM, XOR, ID, RBRACKET, ASN, EXIT  }); newl();
        pass &= test_next("xprint('hello');"   , { ID, LPAREN, STR, RPAREN, ENDL, EXIT              }); newl();
        pass &= test_next("fn entry() byte {}" , { ID, ID, LPAREN, RPAREN, ID, LBRACE, RBRACE, EXIT }); newl();

        idt = old_idt;
        return pass;
    }
}
