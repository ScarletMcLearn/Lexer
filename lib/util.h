#include "dfa.h"
using namespace std;

class AllSets{
    set<char> _S;                   ///     _S = a|b|...|z|A|B|....|Z|_
    set<char> _N;                   ///     _N = 0|1|...|9
    set<char> _C;                   ///     _C = "
    set<char> _A;                   ///     _A = all printable ASCII chars
    set<char> _D;                   ///     _D = .
    map<string,string> _KEYWORDS;   ///     ALL KEYWORDS

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
        for(int i='32'; i<='127'; i++)   _A.insert((char)i);


        ///     _D = .
        _D.insert('.');


        ///     _KEYWORDS = Allowed keywords in the language
        _KEYWORDS.insert({
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
                         make_pair("return","<RETURN-CONTROL>")
                         });
    }

    bool S(char c) {return(_S.find(c) == _S.end()?false:true);}
    bool N(char c) {return(_N.find(c) == _N.end()?false:true);}
    bool C(char c) {return(_C.find(c) == _C.end()?false:true);}
    bool A(char c) {return(_A.find(c) == _A.end()?false:true);}
    bool D(char c) {return(_D.find(c) == _D.end()?false:true);}
    string Keyword(string c) {return(_KEYWORDS.find(c) == _KEYWORDS.end()?"NULL":_KEYWORDS[c]);}

} Set;
