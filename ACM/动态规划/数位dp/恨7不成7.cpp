#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
const int mod = 1e9 + 7;
typedef long long ll;
int up[25];
ll p[25];
struct node
{
    ll cnt, num, sqnum; //个数，累加和，平方和
    node()
    {
        cnt = -1;
        num = 0;
        sqnum = 0;
    }
    node(ll a, ll b, ll c) : cnt(a), num(b), sqnum(c) {}
} dp[25][8][8];
void init()
{
    memset(dp, -1, sizeof(dp));
    p[1] = 1;
    for (int i = 2; i <= 20; ++i)
        p[i] = p[i - 1] * 10 % mod;
}
node dfs(int deep, int num, int sum, bool flag)
{
    if (!deep)
        return (num != 0 && sum != 0) ? node(1, 0, 0) : node(0, 0, 0);
    if (!flag && dp[deep][num][sum].cnt != -1)
        return dp[deep][num][sum];
    int bound = flag ? up[deep] : 9;
    node tmp, res(0, 0, 0);
    for (int i = 0; i <= bound; ++i)
    {
        if (i == 7)
            continue;
        tmp = dfs(deep - 1, (num * 10 + i) % 7, (sum + i) % 7, flag && i == bound);
        res.cnt = (res.cnt + tmp.cnt) % mod;
        res.num = (res.num + (tmp.num + (tmp.cnt * p[deep] % mod) * i % mod) % mod) % mod;
        res.sqnum = ((res.sqnum + tmp.sqnum % mod) % mod + ((((2 * p[deep] * i) % mod) * tmp.num % mod)) % mod + (((((p[deep] * p[deep]) % mod) * i) % mod) * i % mod) * tmp.cnt % mod) % mod;
    }
    if (!flag)
        dp[deep][num][sum] = res;
    return res;
}
ll solve(ll n)
{
    int deep = 0;
    while (n)
        up[++deep] = n % 10, n /= 10;
    node ans = dfs(deep, 0, 0, true);
    return ans.sqnum;
}
int main()
{
    IOS
    init();
    int t;
    cin >> t;
    while (t--)
    {
        ll l, r;
        cin >> l >> r;
        cout << (solve(r) - solve(l - 1) + mod) % mod << endl;
    }
    return 0;
}
//hdu4507