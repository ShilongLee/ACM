#include <iostream>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;
const int N = 1005;
const int B = 25;
const int NODE = N + B;
const int MAXM = N * B;
int n, b, mapp[N][B], limit[B], mid, master[B][N], len[N];
bool vis[NODE];
bool match(int x, int l, int r)
{
    for (int i = l; i <= r; ++i)
    {
        int y = mapp[x][i];
        if (!vis[y])
        {
            vis[y] = 1;
            if (len[y] < limit[y])
            {
                master[y][++len[y]] = x;
                return true;
            }
            else
            {
                for (int i = 1; i <= len[y]; ++i)
                {
                    if (match(master[y][i],l,r))
                    {
                        master[y][i] = x;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
bool hungry(int l, int r)
{
    for (int i = 1; i <= n; ++i)
    {
        memset(vis, 0, sizeof(vis));
        if (!match(i, l, r))
            return false;
    }
    return true;
}
bool solve()
{
    for (int i = 1; i + mid - 1 <= b; ++i)
    {
        memset(len, 0, sizeof(len));
        if (hungry(i, i + mid - 1))
            return true;
    }
    return false;
}
int main()
{
    cin >> n >> b;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= b; ++j)
            cin >> mapp[i][j];
    for (int i = 1; i <= b; ++i)
        cin >> limit[i];
    int l = 1, r = b;
    while (l <= r)
    {
        mid = (l + r) >> 1;
        if (solve())
            r = mid - 1;
        else
            l = mid + 1;
    }
    cout << l << endl;
    return 0;
}
//poj3189