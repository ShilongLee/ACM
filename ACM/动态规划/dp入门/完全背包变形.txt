#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
const int inf = 0x3f3f3f3f;
const int N = 10005;
int dp[N];
int val[N];
int wgt[N];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n, m, k;
        cin >> n >> m;
        m -= n;
        memset(dp, inf, sizeof(dp));
        dp[0] = 0;
        cin >> k;
        for (int i = 1; i <= k; ++i)
            cin >> val[i] >> wgt[i];
        for (int i = 1; i <= k; ++i)
            for (int j = wgt[i]; j <= m; ++j)
                dp[j] = min(dp[j], dp[j - wgt[i]] + val[i]);
        if (m == 0 || dp[m] == inf)
            cout << "This is impossible." << endl;
        else
            cout << "The minimum amount of money in the piggy-bank is " << dp[m] << "." << endl;
    }
    return 0;
}
//hdu1114