#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 15;
const int T = 100005;
int pie[N][T];
int dp[N][T];
int n, t, tt = 0;
int main()
{
    while (cin >> n && n)
    {
        memset(pie, 0, sizeof(pie));
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; ++i)
        {
            int x, y;
            cin >> x >> y;
            tt = max(tt, y);
            pie[++x][y]++;
        }
        for (int i = tt; i >= 0; --i)
            for (int j = 1; j <= 11; ++j)
                dp[j][i] = max(dp[j - 1][i + 1], max(dp[j][i + 1], dp[j + 1][i + 1])) + pie[j][i];
        cout << dp[6][0] << endl;
    }
    return 0;
}
//hdu1176