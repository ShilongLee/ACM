#include <iostream>
#include <string.h>
#include <stack>
#include <algorithm>
using namespace std;
const int N = 1005;
struct Mouse
{
    int w, v, pos;
    Mouse() {}
    Mouse(int a, int b, int c)
    {
        w = a, v = b, pos = c;
    }
    bool operator<(const Mouse &a) const
    {
        return v > a.v;
    }
} mouse[N];
int dp[N];
int pre[N];
int main()
{
    int a, b, count = 0, ans = 0, num = 1, maxpos = 1;

    while (cin >> a >> b)
    {
        mouse[++count].w = a;
        mouse[count].v = b;
        mouse[count].pos = count;
    }
    sort(mouse + 1, mouse + count + 1);
    for (int i = 1; i <= count; ++i)
        dp[i] = 1;
    for (int i = 1; i <= count; ++i)
    {
        for (int j = i + 1; j <= count; ++j)
        {
            if (mouse[j].w > mouse[i].w && mouse[j].v < mouse[i].v)
                if (dp[j] < dp[i] + 1)
                {
                    dp[j] = dp[i] + 1;
                    pre[j] = i;
                }
            ans = max(ans, dp[j]);
        }
    }
    cout << ans << endl;
    // for (int i = 1; i <= count; ++i)
    //     cout << dp[i] << ' ';
    // cout << endl;
    for (int i = 1; i <= count; ++i)
        if (dp[i] == ans)
            maxpos = i;
    // for (int i = 1; i <= count; ++i)
    //     cout << pre[i] << ' ';
    // cout << endl;
    stack<int> s;
    while (maxpos)
    {
        s.push(mouse[maxpos].pos);
        maxpos = pre[maxpos];
    }
    while(!s.empty())
    {
        cout << s.top() << endl;
        s.pop();
    }
    return 0;
}
//hdu1160