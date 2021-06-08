#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
using namespace std;
const int N = 105;
int dp[N][N];
int main()
{
    string s;
    while (cin >> s && s != "end")
    {
        memset(dp, 0, sizeof(dp));
        int n = s.length();
        for (int r = 2; r <= n; ++r)
            for (int i = 0; i + r - 1 < n; ++i)
            {
                int j = i + r - 1;
                if ((s[i] == '(' && s[j] == ')') || (s[i] == '[' && s[j] == ']'))
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                for (int k = i; k <= j - 1; ++k)
                    dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }
        cout << dp[0][n-1] << endl;
    }
    return 0;
}
//POJ - 2955