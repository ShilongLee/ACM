#include <string.h>
#include <algorithm>
#include <iostream>
using namespace std;
const int N = 1005;
char mapp[N][N];
int n, dp[N][N];
int main()
{
    while (cin >> n && n)
    {
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                cin >> mapp[i][j];
        int ans = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
            {
                if (i == 1 || j == n)
                    dp[i][j] = 1;
                else
                {
                    int x = i - 1, y = j + 1;
                    while (x >= 1 && y <= n && mapp[x][j] == mapp[i][y])
                        --x, ++y;
                    int t = i - x;
                    dp[i][j] = min(dp[i - 1][j + 1] + 1, t);
                }
                ans = max(ans, dp[i][j]);
            }
        cout << ans << endl;
    }
    return 0;
}
//hdu2859