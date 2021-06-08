#include <iostream>
#include <string.h>
#include <queue>
using namespace std;
const int N = 55;
const int M = 55;
const int K = 55;
const int maxm = N * M << 1;
const int inf = 0x3f3f3f3f;
const int NODE = N + M;
int n, m, k, need[N][K], have[M][K], cost[N][M], st, ed;
int v[maxm], flow[maxm], w[maxm], first[maxm], ext[maxm], num, maxflow, mincost, pre[NODE], last[NODE], dis[NODE], f[NODE];
bool vis[NODE];
void init()
{
    memset(first, -1, sizeof(first));
    num = 1;
    maxflow = 0;
}
void inputmatrix()
{
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> cost[i][j];
}
void add(int x, int y, int a, int b)
{
    v[++num] = y;
    flow[num] = a;
    w[num] = b;
    ext[num] = first[x];
    first[x] = num;
}
void build(int kind)
{
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            add(i, j + n, inf, cost[i][j]), add(j + n, i, 0, -cost[i][j]);
    for (int i = 1; i <= n; ++i)
        add(st, i, need[i][kind], 0), add(i, st, 0, 0);
    for (int i = 1; i <= m; ++i)
        add(i + n, ed, have[i][kind], 0), add(ed, i + n, 0, 0);
}
bool spfa(int st, int ed)
{
    memset(dis, inf, sizeof(dis));
    memset(f, inf, sizeof(f));
    memset(vis, false, sizeof(vis));
    dis[st] = 0, vis[st] = true, pre[ed] = -1;
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
            if (flow[i] && dis[p] > dis[now] + w[i])
            {
                dis[p] = dis[now] + w[i];
                pre[p] = now;
                last[p] = i;
                f[p] = min(f[now], flow[i]);
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
void MCMF()
{
    while (spfa(st, ed))
    {
        maxflow += f[ed];
        mincost += dis[ed] * f[ed];
        int v = ed;
        while (v != st)
        {
            flow[last[v]] -= f[ed];
            flow[last[v] ^ 1] += f[ed];
            v = pre[v];
        }
    }
}
void print()
{
    cout << "***************************" << endl;
    for (int i = st; i <= ed; ++i)
    {
        for (int j = first[i]; ~j; j = ext[j])
            cout << v[j] << ' ' << flow[j] << ' ' << w[j] << '\t';
        cout << endl;
    }
    cout << "***************************" << endl;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while (cin >> n >> m >> k && (n || m || k))
    {
        st = mincost = 0, ed = n + m + 1;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= k; ++j)
                cin >> need[i][j];
        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= k; ++j)
                cin >> have[i][j];
        bool flag = false;
        for (int i = 1; i <= k; ++i)
        {
            init();
            inputmatrix();
            if (!flag)
            {
                build(i);
                //print();
                int sum = 0;
                for (int j = 1; j <= n; ++j)
                    sum += need[j][i];
                MCMF();
                if (maxflow != sum)
                    flag = true;
            }
        }
        if (flag)
            cout << -1 << endl;
        else
            cout << mincost << endl;
    }
    return 0;
}
//poj2516