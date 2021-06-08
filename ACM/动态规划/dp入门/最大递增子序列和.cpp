#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 1005;
int a[N];
int dp[N];
int main()
{
    int n;
    while (cin >> n && n)
    {
        int maxx = -1;
        for (int i = 1; i <= n; ++i)
        {
            cin >> a[i];
            dp[i] = a[i];
        }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j < i; ++j)
                if (a[i] > a[j])
                    dp[i] = max(dp[i], dp[j] + a[i]);
                    for (int i = 1; i <= n; ++i)
                        maxx = max(maxx, dp[i]);
                    cout << maxx << endl;
    }
    return 0;
}
//hdu1087