#include <bits/stdc++.h>
using namespace std;
const int N = 15;
typedef long long ll;
ll dp[N][N], a[N];
ll l, r;
ll dfs(int pos, int pre, bool flag, bool k)
{
    if (!pos)
        return 1;
    if (!flag && dp[pos][pre] != -1)
        return dp[pos][pre];
    int up_bound = flag ? a[pos] : 9;
    ll res = 0;
    for (int i = 0; i <= up_bound; ++i)
        if (k || abs(pre - i) >= 2)
            res += dfs(pos - 1, i, flag && (i == up_bound), k && (i == 0));
    if (!flag && !k)
        dp[pos][pre] = res;
    return res;
}
ll solve(ll n)
{
    memset(dp, -1, sizeof(dp));
    int num = 0;
    while (n)
        a[++num] = n % 10, n /= 10;
    return dfs(num, 0, 1, 1);
}
int main()
{
    cin >> l >> r;
    cout << solve(r) - solve(l - 1) << endl;
    return 0;
}
//SCOI2009