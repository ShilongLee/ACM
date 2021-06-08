#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 105;
const int inf = 0x3f3f3f3f;
int a[N], dp[N][N];
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int r = 3; r <= n; ++r)
        for (int i = 1; i + r - 1 <= n; ++i)
        {
            int j = i + r - 1;
            dp[i][j] = inf;
            for (int k = i + 1; k <= j - 1; ++k)//枚举的这个数最后拿走
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j] + a[i] * a[j] * a[k]);
        }
    cout << dp[1][n] << endl;
    return 0;
}
//poj1651