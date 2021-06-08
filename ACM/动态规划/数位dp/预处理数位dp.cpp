#include <bits/stdc++.h>
using namespace std;
const int N = 15;
int dp[N][N], l, r;
void init()
{
    for (int i = 0; i <= 9; ++i)
        dp[1][i] = 1;
    for (int i = 2; i < N; ++i)
        for (int j = 0; j <= 9; ++j)
            for (int k = j; k <= 9; ++k)
                dp[i][j] += dp[i - 1][k];
}
int solve(int n)
{
    if (!n)
        return 1;
    vector<int> ve;
    while (n)
        ve.push_back(n % 10), n /= 10;
    int res = 0;
    int last = 0;
    for (int i = ve.size() - 1; i >= 0; --i)
    {
        int x = ve[i];
        for (int j = last; j < x; ++j)
            res += dp[i + 1][j];
        if (x < last)
            break;
        last = x;
        if (!i)
            res++;
    }
    return res;
}
int main()
{
    init();
    cin >> l >> r;
    cout << solve(r) - solve(l - 1) << endl;
    return 0;
}
//acWing数字游戏