#include <iostream>
#include <string.h>
#include <queue>
using namespace std;
const int N = 5e3 + 5;
const int M = 1e5+5;
int n, m, s, t, flow[N], dis[N], pre[N], last[N], maxflow, mincost;
int v[M], f[M], w[M], first[M], ext[M], num;
bool vis[N];
void init()
{
    num = 1;
    maxflow = mincost = 0;
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
bool spfa(int st,int ed)
{
    memset(dis, 0x7f, sizeof(dis));
    memset(flow, 0x7f, sizeof(flow));
    memset(vis, false, sizeof(vis));
    dis[st] = 0, pre[ed] = -1, vis[st] = true;
    queue<int> q;
    q.push(st);
    while (!q.empty())
    {
        int k = q.front();
        q.pop();
        vis[k] = false;
        for (int i = first[k]; ~i; i = ext[i])
        {
            int p = v[i];
            if (f[i] && dis[p] > dis[k] + w[i])
            {
                dis[p] = dis[k] + w[i];
                flow[p] = min(flow[k], f[i]);
                pre[p] = k;
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
    cin >> n >> m >> s >> t;
    init();
    for (int i = 1; i <= m; ++i)
    {
        int x, y, f, w;
        cin >> x >> y >> f >> w;
        add(x, y, f, w);
        add(y, x, 0, -w);
    }
    while (spfa(s,t))
    {
        maxflow += flow[t];
        mincost += dis[t]*flow[t];
        int v = t;
        while (v != s)
        {
            f[last[v]] -= flow[t];
            f[last[v] ^ 1] += flow[t];
            v = pre[v];
        }
    }
    cout << maxflow << ' ' << mincost << endl;
    return 0;
}
//洛谷3381