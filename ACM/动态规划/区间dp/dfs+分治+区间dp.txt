#include <iostream>
#include <string>
#include <string.h>
#include <stack>
using namespace std;
const int N = 705;
const int mod = 1e9 + 7;
long long dp[N][N][3][3]; //0 无色 1红色 2蓝色
int match[N];
char str[N];
stack<int> s;
void init(int n)
{
    for (int i = 1; i <= n; ++i)
        if (str[i] == '(')
            s.push(i);
        else
        {
            match[s.top()] = i;
            s.pop();
        }
}
void dfs(int l, int r)
{
    if (l + 1 == r)
    {
        dp[l][r][0][1] = dp[l][r][1][0] = 1;
        dp[l][r][0][2] = dp[l][r][2][0] = 1;
        return;
    }
    if (match[l] == r)
    {
        dfs(l + 1, r - 1);
        for (int i = 0; i <= 2; ++i)
            for (int j = 0; j <= 2; ++j)
            {
                if (j != 1)
                    dp[l][r][0][1] = (dp[l][r][0][1] + dp[l + 1][r - 1][i][j]) % mod;
                if (i != 1)
                    dp[l][r][1][0] = (dp[l][r][1][0] + dp[l + 1][r - 1][i][j]) % mod;
                if (j != 2)
                    dp[l][r][0][2] = (dp[l][r][0][2] + dp[l + 1][r - 1][i][j]) % mod;
                if (i != 2)
                    dp[l][r][2][0] = (dp[l][r][2][0] + dp[l + 1][r - 1][i][j]) % mod;
            }
    }
    else
    {
        int pair_match = match[l];
        dfs(l, pair_match);
        dfs(pair_match + 1, r);
        for (int i = 0; i <= 2; ++i)
            for (int j = 0; j <= 2; ++j)
                for (int x = 0; x <= 2; ++x)
                    for (int y = 0; y <= 2; ++y)
                        if (j != x || (j == 0 && x == 0))
                            dp[l][r][i][y] = (dp[l][r][i][y] + (dp[l][pair_match][i][j] * dp[pair_match + 1][r][x][y]) % mod) % mod;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    memset(dp, 0, sizeof(dp));
    cin >> str + 1;
    int len = strlen(str + 1);
    init(len);
    dfs(1, len);
    long long ans = 0;
    for (int i = 0; i <= 2; ++i)
        for (int j = 0; j <= 2; ++j)
            ans = (ans + dp[1][len][i][j]) % mod;
    cout << ans << endl;
    return 0;
}
//CodeForces - 149D