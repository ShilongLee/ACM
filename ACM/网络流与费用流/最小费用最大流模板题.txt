#include <iostream>
#include <string.h>
#include <math.h>
#include <queue>
using namespace std;
const int N = 1e4 + 5;
const int M = 105;
const int maxm = N * M;
const int inf = 0x3f3f3f3f;
int n, m, Hx[M], Hy[M], mx[M], my[M], numH, numm, v[maxm], w[maxm], f[maxm], first[maxm], ext[maxm], num, flow[N], dis[N], st, ed, maxflow, mincost, pre[N], last[N];
bool vis[N];
void init()
{
    numH = numm = maxflow = mincost = 0;
    num = 1;
    memset(first, -1, sizeof(first));
}
void add(int x, int y, int a, int b)
{
    v[++num] = y;
    f[num] = a;
    w[num] = b;
    ext[num] = first[x];
    first[x] = num;
}
bool spfa(int st, int ed)
{
    memset(dis, inf, sizeof(dis));
    memset(flow, inf, sizeof(flow));
    memset(vis, false, sizeof(vis));
    dis[st] = 0;
    pre[ed] = -1;
    vis[st] = true;
    queue<int> q;
    q.push(st);
    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        vis[now] = false;
        for (int i = first[now]; ~i; i = ext[i])
        {
            int p = v[i];
            if (f[i] && dis[p] > dis[now] + w[i])
            {
                dis[p] = dis[now] + w[i];
                flow[p] = min(f[i], flow[now]);
                pre[p] = now;
                last[p] = i;
                if (!vis[p])
                {
                    vis[p] = true;
                    q.push(p);
                }
            }
        }
    }
    return pre[ed] != -1;
}
int main()
{
    while (cin >> n >> m&&(n||m))
    {
        init();
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
            {
                char c;
                cin >> c;
                if (c == 'm')
                    mx[++numm] = i, my[numm] = j;
                if (c == 'H')
                    Hx[++numH] = i, Hy[numH] = j;
            }
        for (int i = 1; i <= numm; ++i)
        {
            for (int j = 1; j <= numH; ++j)
            {
                int dis = abs(mx[i] - Hx[j]) + abs(my[i] - Hy[j]);
                add(i, j + numm, 1, dis);
                add(j + numm, i, 0, -dis);
            }
        }
        st = 0, ed = numm + numH + 1;
        for (int i = 1; i <= numm; ++i)
        {
            add(st, i, 1, 0);
            add(i, st, 0, 0);
        }
        for (int i = 1; i <= numH; ++i)
        {
            add(i + numm, ed, 1, 0);
            add(ed, i + numm, 0, 0);
        }
        while (spfa(st, ed))
        {
            maxflow += flow[ed];
            mincost += dis[ed] * flow[ed];
            int v = ed;
            while (v != st)
            {

                f[last[v]] -= flow[ed];
                f[last[v] ^ 1] += flow[ed];
                v = pre[v];
            }
        }
        cout << mincost << endl;
    }
    return 0;
}
//poj2195