#include <iostream>
#include <string.h>
#include <algorithm>
#include <queue>
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 105;
const int M = 2005;
const int inf = 0x7f7f7f7f;
int n, m, st, ed, u[M], v[M], w[M], first[M], ext[M], num, cur[M], depth[N], gap[N], col[N];
void add(int x, int y, int z)
{
    v[++num] = y;
    u[num] = x;
    w[num] = z;
    ext[num] = first[x];
    first[x] = num;
}
void bfs()
{
    memset(depth, -1, sizeof(depth));
    memset(gap, 0, sizeof(gap));
    depth[ed] = 0;
    gap[0]++;
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
        depth[st] = n;
    gap[++depth[now]]++;
    return sum;
}
void ISAP()
{
    bfs();
    int ans = 0;
    while (depth[st] < n)
    {
        memcpy(cur, first, sizeof(first));
        ans += dfs(st, inf);
    }
    return;
}
void mark(int st)
{
    if (col[st])
        return;
    col[st] = 1;
    for (int i = first[st]; ~i; i = ext[i])
        if (w[i])
            mark(v[i]);
}
int main()
{
    IOS;
    while (cin >> n >> m && (n || m))
    {
        st = num = 1, ed = 2;
        memset(first, -1, sizeof(first));
        memset(col, 0, sizeof(col));
        for (int i = 1; i <= m; ++i)
        {
            int x, y, z;
            cin >> x >> y >> z;
            add(x, y, z);
            add(y, x, z);
        }
        ISAP();
        mark(st);
        for (int i = 2; i <= num; i += 2)
            if (col[u[i]] != col[v[i]])
                cout << u[i] << ' ' << v[i] << endl;
        cout << endl;
    }
    return 0;
}
//UVA10480