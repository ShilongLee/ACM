#include <iostream>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;
const int N = 205;
const int M = 10005;
const int inf = 2147483647;
int n, m, s, t, v[M], w[M], first[M], ext[M], num, depth[N], gap[N], cur[M];
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
            q.push(p);
            depth[p] = depth[f] + 1;
            gap[depth[p]]++;
        }
    }
    return;
}
int dfs(int st, int flow)
{
    if (st == t)
        return flow;
    int sum = 0;
    for (int &i = cur[st]; ~i; i = ext[i])
    {
        int p = v[i];
        if (w[i] && depth[p] == depth[st] - 1)
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
    if (!(--gap[depth[st]]))
        depth[s] = n;
    gap[++depth[st]]++;
    return sum;
}
long long ISAP()
{
    bfs();
    long long res = 0;
    while (depth[s] < n)
    {
        memcpy(cur, first, sizeof(first));
        res += dfs(s, inf);
    }
    return res;
}
int main()
{
    memset(first, -1, sizeof(first));
    num = 1;
    cin >> n >> m >> s >> t;
    for (int i = 1; i <= m; ++i)
    {
        int x, y, z;
        cin >> x >> y >> z;
        add(x, y, z), add(y, x, 0);
    }
    long long ans = ISAP();
    cout << ans << endl;
    return 0;
}
//洛谷3376