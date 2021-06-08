#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;
const int NODE = 105;
const int M = NODE * NODE << 1;
const int inf = 0x7fffffff;
int n, np, nc, m, v[M], w[M], first[M], ext[M], num, st, ed, cur[M], depth[NODE], gap[NODE];
char str[55];
void init()
{
    num = 1;
    memset(first, -1, sizeof(first));
}
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
    depth[ed] = 0;
    gap[0] = 1;
    queue<int> q;
    q.push(ed);
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
    if (now == ed)
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
            flow -= t;
            sum += t;
            if (flow == 0)
                return sum;
        }
    }
    if (!(--gap[depth[now]]))
        depth[st] = n + 2;
    gap[++depth[now]]++;
    return sum;
}
int ISAP()
{
    bfs();
    int ans = 0;
    while (depth[st] < n + 2)
    {
        memcpy(cur, first, sizeof(first));
        ans += dfs(st, inf);
    }
    return ans;
}
int main()
{
    while (~scanf("%d%d%d%d", &n, &np, &nc, &m))
    {
        init();
        st = 0, ed = n + 1;
        for (int i = 1; i <= m; ++i)
        {
            int x, y, z;
            scanf("%s", str);
            sscanf(str, "(%d,%d)%d", &x, &y, &z);
            add(x+1, y+1, z);
            add(y+1, x+1, 0);
        }
        for (int i = 1; i <= np; ++i)
        {
            int x, y, z;
            char c;
            scanf("%s", str);
            sscanf(str, "(%d)%d", &x, &z);
            add(st, x+1, z);
            add(x+1, st, 0);
        }
        for (int i = 1; i <= nc; ++i)
        {
            int x, y, z;
            char c;
            scanf("%s", str);
            sscanf(str, "(%d)%d", &x, &z);
            add(x+1, ed, z);
            add(ed, x+1, 0);
        }
        int ans = ISAP();
        printf("%d\n", ans);
    }
    return 0;
}
//poj1459