#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;
const int F = 1005;
const int D = 1005;
const int N = 1005;
const int M = (F * N + D * N);
const int NODE = (F + N + N + D);
const int inf = 0x7f7f7f7f;
int f, n, d, st, ed;
int v[M], w[M], first[M], ext[M], num, depth[NODE], gap[NODE], cur[M];
vector<int> likef[N];
vector<int> liked[N];
void init()
{
    memset(first, -1, sizeof(first));
    for (int i = 0; i < F; ++i)
        likef[i].clear();
    for (int i = 0; i < D; ++i)
        liked[i].clear();
    num = 1;
}
void add(int x, int y, int z)
{
    v[++num] = y;
    w[num] = z;
    ext[num] = first[x];
    first[x] = num;
}
void build()
{
    for (int i = 1; i <= f; ++i)
        add(st, i, 1), add(i, st, 0);
    for (int i = 1; i <= n; ++i)
    {
        int siz = likef[i].size();
        for (int j = 0; j < siz; ++j)
        {
            add(likef[i][j], i + f, 1);
            add(i + f, likef[i][j], 0);
        }
        add(i + f, i + f + n, 1), add(i + f + n, i + f, 0);
        siz = liked[i].size();
        for (int j = 0; j < siz; ++j)
        {
            add(i + f + n, f + n + n + liked[i][j], 1);
            add(f + n + n + liked[i][j], i + f + n, 0);
        }
    }
    for (int i = 1; i <= d; ++i)
        add(i + f + n + n, ed, 1), add(ed, i + f + n + n, 0);
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
        depth[st] = f + n + n + d + 2;
    gap[++depth[now]]++;
    return sum;
}
int ISAP()
{
    bfs();
    int ans = 0;
    while (depth[st] < f + n + n + d + 2)
    {
        memcpy(cur, first, sizeof(first));
        ans += dfs(st, inf);
    }
    return ans;
}
int main()
{
    while (cin >> n >> f >> d)
    {
        init();
        st = 0, ed = f + n + n + d + 1;
        for (int i = 1; i <= n; ++i)
        {
            int F, D, a;
            cin >> F >> D;
            for (int j = 1; j <= F; ++j)
            {
                cin >> a;
                likef[i].push_back(a);
            }
            for (int j = 1; j <= D; ++j)
            {
                cin >> a;
                liked[i].push_back(a);
            }
        }
        build();
        int ans = ISAP();
        cout << ans << endl;
    }
    return 0;
}
//poj3281