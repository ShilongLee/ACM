#include <iostream>
#include <string.h>
#include <queue>
using namespace std;
const int N = 505;
const int M = 100005;
const int inf = 0x3f3f3f3f;
int n, m, s, t, v[M], w[M], first[M], ext[M], num, cur[M], depth[N], gap[N];
void add(int x, int y, int z)
{
    v[++num] = y;
    w[num] = z;
    ext[num] = first[x];
    first[x] = num;
}
void bfs()
{
    memset(depth, -1, sizeof(depth));
    memset(gap, 0, sizeof(gap));
    depth[t] = 0;
    gap[0] = 1;
    queue<int> q;
    q.push(t);
    while (!q.empty())
    {
        int f = q.front();
        q.pop();
        for (int i = first[f]; ~i; i = ext[i])
        {
            int p = v[i];
            if (depth[p] != -1)
                continue;
            depth[p] = depth[f] + 1;
            gap[depth[p]]++;
            q.push(p);
        }
    }
    return;
}
int dfs(int now, int flow)
{
    if (now == t)
        return flow;
    int sum = 0;
    for (int &i = cur[now]; ~i; i = ext[i])
    {
        int p = v[i];
        if (w[i] && depth[p] == depth[now] - 1)
        {
            int t = dfs(p, min(flow, w[i]));
            w[i] -= t;
            w[i ^ 1] += t;
            sum += t;
            flow -= t;
            if (!flow)
                return sum;
        }
    }
    if (!(--gap[depth[now]]))
        depth[s] = 2 * n;
    gap[++depth[now]]++;
    return sum;
}
int ISAP()
{
    bfs();
    int ans = 0;
    while (depth[s] < 2 * n)
    {
        memcpy(cur, first, sizeof(first));
        ans += dfs(s, inf);
    }
    return ans;
}
int main()
{
    while (cin >> n >> m >> s >> t)
    {
        t += n;
        num = 1;
        memset(first, -1, sizeof(first));
        for (int i = 1; i <= n; ++i)
        {
            int w;
            cin >> w;
            add(i, i + n, w);
            add(i + n, i, 0);
        }
        for (int i = 1; i <= m; ++i)
        {
            int u, v;
            cin >> u >> v;
            add(u + n, v, inf);
            add(v, u + n, 0);
            add(v + n, u, inf);
            add(u, v + n, 0);
        }
        cout << ISAP() << endl;
    }
    return 0;
}
//hdu4289