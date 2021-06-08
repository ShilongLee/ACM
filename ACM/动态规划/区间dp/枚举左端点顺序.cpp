#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 105;
const int inf = 0x3f3f3f3f;
int d[N];
int sum[N];
int dp[N][N];
int main()
{
    int t, cas = 0;
    cin >> t;
    while (t--)
    {
        memset(dp, 0, sizeof(dp));
        int n;
        cin >> n;
        for (int i = 1; i <= n; ++i)
        {
            cin >> d[i];
            sum[i] = sum[i - 1] + d[i];
        }
        for (int i = 1; i <= n; ++i)
            for (int j = i + 1; j <= n; ++j)
                dp[i][j] = inf;
        for (int r = 2; r <= n; ++r)
            for (int i = 1; i + r - 1 <= n; ++i)
            {
                int j = i + r - 1;
                for (int k = 1; k <= j - i + 1; ++k)
                    dp[i][j] = min(dp[i][j], (k - 1) * d[i] + dp[i + 1][i + k - 1] + dp[i + k][j] + k * (sum[j] - sum[i + k - 1]));
            }
        cout << "Case #" << ++cas << ": " << dp[1][n] << endl;
    }
    return 0;
}
//hdu4283