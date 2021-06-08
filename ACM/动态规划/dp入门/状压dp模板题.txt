#include <iostream>
#include <string.h>
#include <string>
#include <stack>
#include <algorithm>
using namespace std;
const int N = 20;
const int inf = 0x3f3f3f3f;
struct node
{
    int d, c;
    string s;
} hw[N];
struct state
{
    int tim;
    int score;
    int pre;
    string s;
} dp[1 << 15];
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            cin >> hw[i].s >> hw[i].d >> hw[i].c;
        int end = 1 << n;
        for (int i = 1; i < end; ++i)
        {
            dp[i].score = inf;
            for (int j = n - 1; j >= 0; --j)
            {
                int temp = 1 << j;
                if (i & temp)
                {
                    int tmp = i - temp;
                    int t = dp[tmp].tim + hw[j].c - hw[j].d;
                    if (t < 0)
                        t = 0;
                    if (dp[tmp].score + t < dp[i].score)
                    {
                        dp[i].score = dp[tmp].score + t;
                        dp[i].pre = tmp;
                        dp[i].s = hw[j].s;
                        dp[i].tim = dp[tmp].tim + hw[j].c;
                    }
                }
            }
        }
        cout << dp[end - 1].score << endl;
        int tmp = end - 1;
        stack<string> s;
        while (dp[tmp].tim)
        {
            s.push(dp[tmp].s);
            tmp = dp[tmp].pre;
        }
        while (!s.empty())
        {
            cout << s.top() << endl;
            s.pop();
        }
    }
    return 0;
}
//hdu1074