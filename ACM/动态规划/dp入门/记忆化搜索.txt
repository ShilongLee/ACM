#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 2005;
int mapp[N][N];
int dp[N][N];
int n, step;
int dir[4][2] = {0, 1, 0, -1, 1, 0, -1, 0};
int dfs(int x, int y)
{
    if (dp[x][y])
        return dp[x][y];
    int maxx = 0;
    for (int i = 1; i <= step; ++i)
        for (int j = 0; j < 4; ++j)
        {
            int xx = x + dir[j][0] * i;
            int yy = y + dir[j][1] * i;
            if (xx >= 1 && xx <= n && yy >= 1 && yy <= n && mapp[xx][yy] > mapp[x][y])
                maxx = max(maxx, dfs(xx, yy));
        }
    return dp[x][y] = mapp[x][y] + maxx;
}
int main()
{
    while (cin >> n >> step && (n != -1 || step != -1))
    {
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                cin >> mapp[i][j];
        cout << dfs(1, 1) << endl;
    }
    return 0;
}
//hdu1078