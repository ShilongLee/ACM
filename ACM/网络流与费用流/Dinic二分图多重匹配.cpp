#include <iostream>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;
const int K = 35;
const int C = 205;
const int M = 20;
const int inf = 0x3f3f3f3f;
const int NODE = K + C;
const int MAXM = NODE * NODE;
int mapp[NODE][NODE];
int k, c, m, st, ed, mid, v[MAXM], w[MAXM], first[MAXM], ext[MAXM], num, cur[MAXM], depth[NODE];
void floyd()
{
    for (int t = 1; t <= k + c; ++t)
        for (int i = 1; i <= k + c; ++i)
            for (int j = 1; j <= k + c; ++j)
                mapp[i][j] = min(mapp[i][j], mapp[i][t] + mapp[t][j]);
}
void add(int x, int y, int z)
{
    v[++num] = y;
    w[num] = z;
    ext[num] = first[x];
    first[x] = num;
}
void addedge()
{
    memset(first, -1, sizeof(first));
    num = 1;
    for (int i = 1; i <= k; ++i)
    {
        add(st, i, m), add(i, st, 0);
        for (int j = k + 1; j <= k + c; ++j)
            if (mapp[i][j] <= mid)
                add(i, j, 1), add(j, i, 0);
    }
    for (int i = k + 1; i <= k + c; ++i)
        add(i, ed, 1), add(ed, i, 0);
}
bool bfs()
{
    queue<int> q;
    memset(depth, 0, sizeof(depth));
    depth[st] = 1;
    q.push(st);
    while (!q.empty())
    {
        int f = q.front();
        q.pop();
        for (int i = first[f]; ~i; i = ext[i])
        {
            int p = v[i];
            if (w[i] && !depth[p])
            {
                depth[p] = depth[f] + 1;
                q.push(p);
            }
        }
    }
    return depth[ed];
}
int dfs(int st, int flow)
{
    if (st == ed)
        return flow;
    int sum = 0;
    for (int &i = cur[st]; ~i; i = ext[i])
    {
        int p = v[i];
        if (w[i] && depth[p] == depth[st] + 1)
        {
            int t = dfs(p, min(flow, w[i]));
            w[i] -= t;
            w[i ^ 1] += t;
            sum += t;
            flow -= t;
            if (flow == 0)
                return sum;
        }
    }
    if (!sum)
        depth[st] = 0;
    return sum;
}
bool dinic()
{
    addedge();
    int ans = 0;
    while (bfs())
    {
        memcpy(cur, first, sizeof(first));
        ans += dfs(st, inf);
    }
    if (ans == c)
        return true;
    else
        return false;
}
int main()
{
    cin >> k >> c >> m;
    st = 0, ed = k + c + 1;
    for (int i = 1; i <= k + c; ++i)
        for (int j = 1; j <= k + c; ++j)
        {
            cin >> mapp[i][j];
            if (!mapp[i][j] && i != j)
                mapp[i][j] = inf;
        }
    floyd();
    int l = 0, r = inf;
    while (l <= r)
    {
        mid = (l + r) >> 1;
        if (dinic())
            r = mid - 1;
        else
            l = mid + 1;
    }
    cout << l << endl;
    return 0;
}
//poj2112