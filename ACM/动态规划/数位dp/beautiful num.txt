#include <iostream>
#include <map>
#include <string.h>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
const int mod = 2520;
map<int, int> mp;
long long a[25], dp[25][2525][55];
void init()
{
    int cnt = 0;
    mp.clear();
    for (int i = 1; i <= mod; ++i)
        if (mod % i == 0)
            mp[i] = ++cnt;
}
int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}
int LCM(int a, int b)
{
    if (a == 0 || b == 0)
        return a + b;
    return a * b / gcd(a, b);
}
long long dfs(int deep, int num, int lcm, int flag)
{
    if (deep == 0)
        return (num % lcm == 0);
    if (!flag && dp[deep][num][mp[lcm]] != -1)
        return dp[deep][num][mp[lcm]];
    int bound = flag ? a[deep] : 9;
    long long  res = 0;
    for (int i = 0; i <= bound; ++i)
        res += dfs(deep - 1, (num * 10 + i) % mod, LCM(lcm, i), flag && i == bound);
    if (!flag)
        dp[deep][num][mp[lcm]] = res;
    return res;
}
long long solve(ull n)
{
    int deep = 0;
    while (n)
        a[++deep] = n % 10, n /= 10;
    return dfs(deep, 0, 1, 1);
}
int main()
{
    init();
    int t;
    cin >> t;
    memset(dp, -1, sizeof(dp));
    while (t--)
    {
        ull l, r;
        cin >> l >> r;
        cout << solve(r) - solve(l - 1) << endl;
    }
    return 0;
}
//CodeForces - 55D