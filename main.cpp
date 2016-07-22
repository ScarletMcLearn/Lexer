#include <bits/stdc++.h>
using namespace std;

struct trio
{
    int state;
    int lastState;
    int index;
};
trio make_trio(int _state,int _lastState,int _index)
{
    trio tr;
    tr.index = _index;
    tr.state = _state;
    tr.lastState = _lastState;
    return tr;
}

class AllSets
{
    set<char> _S;                   ///     _S = a|b|...|z|A|B|....|Z|_
    set<char> _N;                   ///     _N = 0|1|...|9
    set<char> _C;                   ///     _C = "
    set<char> _A;                   ///     _A = all printable ASCII chars
    set<char> _D;                   ///     _D = .
    set<char> _W;                   ///     _W = \n|\t|<space>|\0
    map<string,string> _KEY;        ///     ALL keywords
    map<string,string> _PUNC;       ///     ALL Punctuates
    map<string,string> _OP;         ///     ALL Operators

public:

    AllSets()
    {
        ///     _S = a|b|...|z|A|B|....|Z|_
        for(int i='A'; i<='Z'; i++)   _S.insert((char)i);
        for(int i='a'; i<='z'; i++)   _S.insert((char)i);
        _S.insert('_');


        ///     _N = 0|1|...|9
        for(int i='0'; i<='9'; i++)   _N.insert((char)i);


        ///     _C = "
        _C.insert('"');


        ///     _A = all printable ASCII chars
        for(int i=32; i<=126; i++) if(i != (int)'"')  _A.insert((char)i);


        ///     _D = .
        _D.insert('.');


        ///     _W = \n|\t|<space>|\0
        _W.insert(
        {
            '\n',
            '\t',
            ' ',
            '\0'
        });


        ///     _KEY = Allowed keywords in the language
        _KEY.insert(
        {
            make_pair("int","<INT-TYPE>"),
            make_pair("char","<CHAR-TYPE>"),
            make_pair("float","<FLOAT-TYPE>"),
            make_pair("double","<DOUBLE-TYPE>"),
            make_pair("string","<STRING-TYPE>"),
            make_pair("void","<VOID-TYPE>"),
            make_pair("signed","<TYPE-MODIFIER-SIGNED>"),
            make_pair("unsigned","<TYPE-MODIFIER-UNSIGNED>"),
            make_pair("if","<IF-CONDITION>"),
            make_pair("else","<ELSE-CONDITION>"),
            make_pair("switch","<SWITCH>"),
            make_pair("case","<CASE>"),
            make_pair("default","<DEFAULT>"),
            make_pair("for","<FOR-LOOP>"),
            make_pair("while","<WHILE-LOOP>"),
            make_pair("do","<DO-WHILE-LOOP>"),
            make_pair("break","<BREAK-CONTROL>"),
            make_pair("continue","<CONTINUE-CONTROL>"),
            make_pair("main","<MAIN>"),
            make_pair("return","<RETURN-CONTROL>")
        });


        ///     _PUNC = All punctuates
        _PUNC.insert(
        {
            make_pair("[","<[>"),
            make_pair("]","<]>"),
            make_pair("(","<(>"),
            make_pair(")","<)>"),
            make_pair("{","<{>"),
            make_pair("}","<}>"),
            make_pair(",","<,>"),
            make_pair(";","<;>"),
            make_pair("#","<#>")
        });


        ///     _OP = All operators
        _OP.insert(
        {
            make_pair("+","<ARITH-ADD-OP>"),
            make_pair("-","<ARITH-SUB-OP>"),
            make_pair("*","<ARITH-MUL-OP>"),
            make_pair("/","<ARITH-DIV-OP>"),
            make_pair("%","<ARITH-MOD-OP>"),

            make_pair("<","<RELAT-LESS-OP>"),
            make_pair("<=","<RELAT-LESS-EQUAL-OP>"),
            make_pair(">=","<RELAT-GREAT-EQUAL-OP>"),
            make_pair(">","<RELAT-GREAT-OP>"),
            make_pair("==","<RELAT-EQUAL-OP>"),
            make_pair("!=","<RELAT-NOT-EQUAL-OP>"),

            make_pair("&&","<LOGIC-AND-OP>"),
            make_pair("||","<LOGIC-OR-OP>"),
            make_pair("!","<LOGIC-NOT-OP>"),

            make_pair("&","<BIT-AND-OP>"),
            make_pair("|","<BIT-OR-OP>"),
            make_pair("^","<BIT-XOR-OP>"),
            make_pair("<<","<BIT-SHLEFT-OP>"),
            make_pair(">>","<BIT-SHRIGHT-OP>"),


            make_pair("=","<ASN-OP>"),
            make_pair("%=","<ASN-MOD-OP>"),
            make_pair("/=","<ASN-DIV-OP>"),
            make_pair("*=","<ASN-MUL-OP>"),
            make_pair("+=","<ASN-ADD-OP>"),
            make_pair("-=","<ASN-SUB-OP>"),
            make_pair("++","<ASN-INC-OP>"),
            make_pair("--","<ASN-DEC-OP>"),
        });

    }

    bool S(char c)
    {
        return(_S.find(c) == _S.end()?false:true);
    }
    bool N(char c)
    {
        return(_N.find(c) == _N.end()?false:true);
    }
    bool C(char c)
    {
        return(_C.find(c) == _C.end()?false:true);
    }
    bool A(char c)
    {
        return(_A.find(c) == _A.end()?false:true);
    }
    bool D(char c)
    {
        return(_D.find(c) == _D.end()?false:true);
    }
    bool W(char c)
    {
        return(_W.find(c) == _W.end()?false:true);
    }
    string Key(string c)
    {
        return(_KEY.find(c) == _KEY.end()?"NULL":_KEY[c]);
    }
    string Punc(string c)
    {
        return(_PUNC.find(c) == _PUNC.end()?"NULL":_PUNC[c]);
    }
    string Op(string c)
    {
        return(_OP.find(c) == _OP.end()?"NULL":_OP[c]);
    }

} Set;

class DFA
{

    map<int, string> descState;
    vector<string> tokens;
public:
    DFA()
    {
        descState.insert(
        {
            make_pair(7, "<STRING>"),
            make_pair(2, "<ID>"),
            make_pair(8, "<ERROR-Ending Double quote Expected>"),
            make_pair(3, "<ERROR-Ending Double quote Expected>"),
            make_pair(4, "<ERROR-Real Number error>"),
            make_pair(5, "<ID>"),
            make_pair(6, "<ID>"),
            make_pair(1, "<NUM>"),
            make_pair(9, "<NUM-FLOATING>"),
            make_pair(10, "<ERROR>")
        });

    }

    trio check(string str)
    {
        int state=0, lastState=0, i = 0;
        for(; true; i++)
        {
            switch(state)
            {
            case 0:
                if(Set.S(str[i]))
                {
                    state = 2;
                    lastState = 0;
                }
                else if(Set.N(str[i]))
                {
                    state = 1;
                    lastState = 0;
                }
                else if(Set.C(str[i]))
                {
                    state = 3;
                    lastState = 0;
                }
                else
                {
                    lastState = 0;
                    state = 10;
                }
                break;
            case 1:
                if(Set.N(str[i]))
                {
                    state = 1;
                    lastState = 1;
                }
                else if(Set.D(str[i]))
                {
                    state = 4;
                    lastState = 1;
                }
                else
                {
                    lastState = 1;
                    state = 10;
                }
                break;
            case 4:
                if(Set.N(str[i]))
                {
                    state = 9;
                    lastState = 4;
                }
                else
                {
                    lastState = 4;
                    state = 10;
                }
                break;
            case 9:
                if(Set.N(str[i]))
                {
                    state = 9;
                    lastState = 9;
                }
                else
                {
                    lastState = 9;
                    state = 10;
                }
                break;
            case 2:
                if(Set.N(str[i]))
                {
                    state = 5;
                    lastState = 2;
                }
                else if(Set.S(str[i]))
                {
                    state = 6;
                    lastState = 2;
                }
                else
                {
                    lastState = 2;
                    state = 10;
                }
                break;
            case 5:
                if(Set.N(str[i]))
                {
                    state = 5;
                    lastState = 5;
                }
                else if(Set.S(str[i]))
                {
                    state = 6;
                    lastState = 5;
                }
                else
                {
                    lastState = 5;
                    state = 10;
                }
                break;
            case 6:
                if(Set.N(str[i]))
                {
                    state = 5;
                    lastState = 6;
                }
                else if(Set.S(str[i]))
                {
                    state = 6;
                    lastState = 6;
                }
                else
                {
                    lastState = 6;
                    state = 10;
                }
                break;
            case 3:
                if(Set.A(str[i]))
                {
                    state = 8;
                    lastState = 3;
                }
                else if(Set.C(str[i]))
                {
                    state = 7;
                    lastState = 3;
                }
                else
                {
                    lastState = 3;
                    state = 10;
                }
                break;
            case 8:
                if(Set.A(str[i]))
                {
                    state = 8;
                    lastState = 8;
                }
                else if(Set.C(str[i]))
                {
                    state = 7;
                    lastState = 8;
                }
                else
                {
                    lastState = 8;
                    state = 10;
                }
                break;
            case 7:
                lastState = 7;
                if(Set.A(str[i])||
                        Set.C(str[i])||
                        Set.D(str[i])||
                        Set.N(str[i])||
                        Set.S(str[i]))
                {
                    state = 10;
                }
                break;
            case 10:
                i = i-1;
                return make_trio(state,lastState,i);
            }
        }
        return make_trio(state,lastState,i);
    }

    string clrPrefix(string x)
    {
        int xLength = x.length();
        int xStart = 0;

        if(xLength > 1)
        {
            string tx = x.substr(0,2);
            string td = x.substr(0,1);

            if(Set.Punc(tx)!= "NULL")
            {
                tokens.push_back(Set.Punc(tx));
                xStart = 2;
            }
            else if(Set.Op(tx)!= "NULL")
            {
                tokens.push_back(Set.Op(tx));
                xStart = 2;
            }
            else if(Set.Punc(td)!= "NULL")
            {
                tokens.push_back(Set.Punc(td));
                xStart = 1;
            }
            else if(Set.Op(td)!= "NULL")
            {
                tokens.push_back(Set.Op(td));
                xStart = 1;
            }
        }
        else if(xLength == 1)
        {
            if(Set.Punc(x)!="NULL")
            {
                tokens.push_back(Set.Punc(x));
                xStart = 1;
            }
            else if(Set.Op(x)!="NULL")
            {
                tokens.push_back(Set.Op(x));
                xStart = 1;
            }
        }
        string ret = x.substr(xStart,xLength-xStart);
        return ret;
    }

    void detect(string buffer)
    {
        //trio sample = check(buffer);
        //cout<<"Index: "<<sample.index<<endl<<"Last: "<<descState[sample.lastState]<<endl;

        stringstream ss(buffer);
        string words;

        while(ss>>words)
        {
            int wordLength = words.size();
            while(true)
            {
                words = clrPrefix(words);
                if(wordLength == words.size()) break;
                wordLength = words.size();
            }

        }
    }

    vector<string> getTokens()
    {
        return tokens;
    }

    void printTokens()
    {
        cout<<"\n\n\n------------------------TOKENS------------------------\n";
        for(int i=0;i<tokens.size();i++)
        {
            cout<<tokens[i]<<endl;
        }
    }

} dfa;



int main()
{
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);


    string buffer;

    /**/
    while(!cin.eof())
    {
        getline(cin, buffer);
        if(!buffer.empty())
        {
            dfa.detect(buffer);
            dfa.printTokens();
        }
    }

    ///*/

}

