#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
const int K = 2005;
const int inf = 0x3f3f3f3f;
int cost[K];
int ad[K];
int dp[K];
int main()
{
    IOS;
    int t;
    cin >> t;
    while (t--)
    {
        memset(dp, 0, sizeof(dp));
        int k;
        cin >> k;
        for (int i = 1; i <= k; ++i)
            cin >> cost[i];
        for (int i = 1; i <= k - 1; ++i)
            cin >> ad[i];
        dp[1] = cost[1];
        for (int i = 2; i <= k; ++i)
            dp[i] = min(dp[i - 1] + cost[i], dp[i - 2] + ad[i - 1]);
        int tim = dp[k];
        int h = tim / 3600 + 8;
        int m = (tim % 3600) / 60;
        int s = (tim % 3600) % 60;
        if (h > 12)
            printf("%02d:%02d:%02d pm\n", h, m, s);
        else
            printf("%02d:%02d:%02d am\n", h, m, s);
    }
    return 0;
}
//hdu1260