#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
int a[100000005];
int dp[100000005];
int main()
{
    IOS;
    int n;
    while (cin >> n)
    {
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        int pos = 0;
        for (int i = 1; i <= n; ++i)
        {
            if (a[i] > dp[pos])
                dp[++pos] = a[i];
            else
                dp[lower_bound(dp + 1, dp + pos + 1, a[i]) - &dp[0]] = a[i];
        }
        cout << pos << endl;
    }
    return 0;
}
//hdu1257