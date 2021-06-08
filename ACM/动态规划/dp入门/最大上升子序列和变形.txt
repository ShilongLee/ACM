#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
struct node
{
    int l, r, h;
    node() {}
    node(int a, int b, int c)
    {
        l = a;
        r = b;
        h = c;
    }
    bool operator<(const node &a) const
    {
        if (a.l == l)
            return r < a.r;
        return l < a.l;
    }
} brick[205];
int n, dp[205];
int main()
{
    int c = 0;
    while (cin >> n && n)
    {
        int cnt = 0, ans = 0;
        memset(brick, 0, sizeof(brick));
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; ++i)
        {
            int x, y, z;
            cin >> x >> y >> z;
            brick[++cnt] = node(x, y, z);
            brick[++cnt] = node(x, z, y);
            brick[++cnt] = node(y, x, z);
            brick[++cnt] = node(y, z, x);
            brick[++cnt] = node(z, x, y);
            brick[++cnt] = node(z, y, x);
        }
        sort(brick + 1, brick + cnt + 1);
        for (int i = 1; i <= cnt; ++i)
        {
            dp[i] = max(brick[i].h, dp[i]);
            ans = max(ans, dp[i]);
            for (int j = i; j <= cnt; ++j)
                if (brick[j].l > brick[i].l && brick[j].r > brick[i].r)
                    dp[j] = max(dp[j], dp[i] + brick[j].h), ans = max(ans, dp[j]);
        }
        cout << "Case "<<++c<<": maximum height = "<<ans<< endl;
    }
    return 0;
}
//hdu1069