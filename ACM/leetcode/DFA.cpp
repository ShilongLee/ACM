#include <bits/stdc++.h>
using namespace std;
class Automaton
{
public:
    long long ans = 0;
    bool flag = 0;
    string state = "start";
    unordered_map<string, vector<string>> mp = {
        {"start", {"start", "signed", "number", "end"}},
        {"signed", {"end", "end", "number", "end"}},
        {"number", {"end", "end", "number", "end"}},
        {"end", {"end", "end", "end", "end"}}};
    int get_col(char c)
    {
        if (c == ' ')
            return 0;
        else if (c == '+' || c == '-')
            return 1;
        else if (c >= '0' && c <= '9')
            return 2;
        else
            return 3;
    }
    void get(char c)
    {
        state = mp[state][get_col(c)];
        if (state == "signed"&&c=='-')
                flag = 1;
            else if (state == "number")
            {
                ans = ans * 10 + c - '0';
                if (!flag)
                    ans = min(ans, (long long)INT_MAX);
                else
                    ans = min(ans, -(long long)INT_MIN);
            }
    }
};

class Solution
{
public:
    int myAtoi(string s)
    {
        Automaton a;
        for (int i = 0; i < s.length(); ++i)
            a.get(s[i]);
        if(a.flag)
            a.ans = -a.ans;
        return (int)a.ans;
    }
};
int main()
{
    string s;
    cin >> s;
    Solution sol;
    cout << sol.myAtoi(s) << endl;
    return 0;
}
//leetcode P8