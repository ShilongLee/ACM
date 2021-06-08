#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 105;
const int inf = 0x3f3f3f3f;
int a[N];
int dp[N][N];
int main()
{
    int t, cas = 0;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        for (int i = 1; i <= n; ++i)
            dp[i][i] = 1;
        for (int r = 2; r <= n; ++r)
            for (int i = 1; i + r - 1 <= n; ++i)
            {
                int j = i + r - 1;
                dp[i][j] = j - i + 1;
                if (a[i] == a[j])
                    dp[i][j] = dp[i][j - 1];
                for (int k = i; k <= j - 1; ++k)
                    if (a[k] == a[i])
                        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }
        cout << "Case " << ++cas << ": " << dp[1][n] << endl;
    }
    return 0;
}
//LightOJ - 1422