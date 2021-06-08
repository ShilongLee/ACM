#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 2005;
int a[N], n, dp[N][N];
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = n; i >= 1; --i)
    {
        for (int j = i; j <= n; ++j)
        {
            if (i == j)
                dp[i][j] = n * a[i];
            else
                dp[i][j] = max(dp[i + 1][j] + a[i] * (n - j + i), dp[i][j - 1] + a[j] * (n - j + i));
        }
    }
    cout << dp[1][n] << endl;
    return 0;
}
//poj 3186