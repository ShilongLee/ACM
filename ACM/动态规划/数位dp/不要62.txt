#include <iostream>
#include <string.h>
using namespace std;
int l, r;
int bound[15];
int dp[15][2];
int dfs(int pos, int pre, bool flag)
{
    if (!pos)
        return 1;
    if (!flag && dp[pos][pre] != -1)
        return dp[pos][pre];
    int up = flag ? bound[pos] : 9;
    int res = 0;
    for (int i = 0; i <= up; ++i)
    {
        if (i == 4 || (pre && i == 2))
            continue;
        res += dfs(pos - 1, i == 6, flag && i == bound[pos]);
    }
    if (!flag)
        dp[pos][pre] = res;
    return res;
}
int solve(int n)
{
    int m = n, num = 0;
    while (m)
    {
        bound[++num] = m % 10;
        m /= 10;
    }
    return dfs(num, 0, 1);
}
int main()
{
    while (cin >> l >> r && (l || r))
    {
        memset(dp, -1, sizeof(dp));
        cout << solve(r) - solve(l - 1) << endl;
    }
    return 0;
}
//hdu2089