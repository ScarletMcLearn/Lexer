#include <bits/stdc++.h>
using namespace std;

class DFA
{
    string buffer;
    int state, lastState;
    map<int, string> descState;

public:

    void init(string _buffer)
    {
        lastState = state = 0;
        buffer = _buffer;
        descState.insert({
                         make_pair(7, "string"),
                         make_pair(2, "id"),
                         make_pair(5, "id"),
                         make_pair(6, "id"),
                         make_pair(1, "num"),
                         make_pair(9, "num")
                         });
    }

    pair<int,int> check(string str)
    {
        for(int i=0;i<str.length();i++)
        {
            switch(state)
            {
            case 0:
                if(Set.S(buffer[i]))
                {
                    state = 2;
                    lastState = 0;
                }else if(Set.N(buffer[i]))
                {
                    state = 1;
                    lastState = 0;
                }else if(Set.C(buffer[i]))
                {
                    state = 3;
                    lastState = 0;
                }
                else return make_pair(lastState, i);
                break;
            case 1:
                if(Set.N(buffer[i]))
                {
                    state = 1;
                    lastState = 1;
                }else if(Set.D(buffer[i]))
                {
                    state = 4;
                    lastState = 1;
                }
                else return make_pair(lastState, i);
                break;
            case 4:
                if(Set.N(buffer[i]))
                {
                    state = 9;
                    lastState = 4;
                }
                else return make_pair(lastState, i);
                break;
            case 9:
                if(Set.N(buffer[i]))
                {
                    state = 9;
                    lastState = 9;
                }
                else return make_pair(lastState, i);
                break;
            case 2:
                if(Set.N(buffer[i]))
                {
                    state = 5;
                    lastState = 2;
                }else if(Set.S(buffer[i]))
                {
                    state = 6;
                    lastState = 2;
                }
                else return make_pair(lastState, i);
                break;
            case 5:
                if(Set.N(buffer[i]))
                {
                    state = 5;
                    lastState = 5;
                }else if(Set.S(buffer[i]))
                {
                    state = 6;
                    lastState = 5;
                }
                else return make_pair(lastState, i);
                break;
            case 6:
                if(Set.N(buffer[i]))
                {
                    state = 5;
                    lastState = 6;
                }else if(Set.S(buffer[i]))
                {
                    state = 6;
                    lastState = 6;
                }
                else return make_pair(lastState, i);
                break;
            case 3:
                if(Set.A(buffer[i]))
                {
                    state = 8;
                    lastState = 3;
                }else if(Set.C(buffer[i]))
                {
                    state = 7;
                    lastState = 3;
                }
                else return make_pair(lastState, i);
                break;
            case 8:
                if(Set.A(buffer[i]))
                {
                    state = 8;
                    lastState = 8;
                }else if(Set.C(buffer[i]))
                {
                    state = 7;
                    lastState = 8;
                }
                else return make_pair(lastState, i);
                break;
            case 7:
                lastState = 7;
                return make_pair(lastState, i);
                break;
            }
        }
    }
}dfa;













