#include <string.h>
#include<stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 205;
const int M = 25;
const int K = 805;
const int base = 400;
struct node
{
    int x, y;
} a[N];
int n, m, dp[N][M][K], ans[N];
int main()
{
    int cas = 0;
    while (cin >> n >> m && n)
    {
        printf("Jury #%d\n", ++cas);
        memset(ans, 0, sizeof(ans));
        memset(dp, -0x3f, sizeof(dp));
        for (int i = 1; i <= n; ++i)
            cin >> a[i].x >> a[i].y;
        dp[0][0][base] = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 0; j <= m; ++j)
                for (int k = 0; k < K; ++k)
                {
                    dp[i][j][k] = dp[i - 1][j][k];
                    int t = k - (a[i].x - a[i].y);
                    if (t < 0 || t >= K)
                        continue;
                    if (j < 1)
                        continue;
                    dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j - 1][t] + a[i].x + a[i].y);
                }
        int pos = 0;
        while (dp[n][m][base - pos] < 0 && dp[n][m][base + pos] < 0)
            ++pos;
        if (dp[n][m][base - pos] > dp[n][m][base + pos])
            pos = base - pos;
        else
            pos = base + pos;
        int psum = 0, dsum = 0;
        int i = n, j = m, cnt = 0;
        while (j)
        {
            if (dp[i][j][pos] == dp[i - 1][j][pos])
                --i;
            else
            {
                ans[++cnt] = i;
                psum += a[i].x;
                dsum += a[i].y;
                pos -= (a[i].x - a[i].y);
                --i;
                --j;
            }
        }
        printf("Best jury has value %d for prosecution and value %d for defence:\n", psum, dsum);
        sort(ans + 1, ans + 1 + cnt);
        for (int i = 1; i <= cnt; ++i)
            cout << ' ' << ans[i];
        cout << endl
             << endl;
    }
    return 0;
}
//poj1015
//背包空间为800，因为2,3 和3,2不同不能颠倒不能按照绝对值算