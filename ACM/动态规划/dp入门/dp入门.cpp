#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 1000015;
const int M = 105;
const int inf = 1 << 30;
int a[N];
int dp[N];
int max1[N], maxx;
int n, m;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while (cin >> m >> n)
    {
        memset(dp, 0, sizeof(dp));
        memset(max1, 0, sizeof(max1));
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        dp[0] = -inf;
        for (int i = 1; i <= m; ++i)
        {
            maxx = -inf;
            for (int j = i; j <= n; ++j)
            {
                dp[j] = max(dp[j - 1] + a[j], max1[j - 1] + a[j]);
                max1[j - 1] = maxx;
                maxx = max(maxx, dp[j]);
            }
        }
        cout << maxx << endl;
    }
    return 0;
}
//hdu1024