#include <iostream>
#include <string.h>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 550;
const int P = 150;
const int M = N * N << 1;
const int inf = 0x7f7f7f7f;
typedef pair<int, int> pii;
int effort[N], in[N][P], out[N][P], n, p, st, ed, depth[N], gap[N], cur[M], routenum, flag, Msum, cnt;
int u[M], v[M], w[M], first[M], ext[M], num;
stack<int> s;
void init()
{
    memset(first, -1, sizeof(first));
    num = 1;
    routenum = Msum = cnt = 0;
}
void add(int x, int y, int z)
{
    v[++num] = y;
    u[num] = x;
    w[num] = z;
    ext[num] = first[x];
    first[x] = num;
}
void print()
{
    for (int i = 1; i <= 2 * n; ++i)
    {
        cout << "(" << i << ")";
        for (int j = first[i]; ~j; j = ext[j])
            cout << v[j] << ' ';
        cout << endl;
    }
}
void build()
{
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (i == j)
                continue;
            bool flag = true;
            int sum = 0;
            for (int k = 1; k <= p; ++k)
                if (!out[i][k])
                    sum++;
            if (sum == p)
                continue;
            for (int k = 1; k <= p; ++k)
                if ((out[i][k] == 0 && in[j][k] == 1) || (out[i][k] == 1 && in[j][k] == 0))
                {
                    flag = false;
                    break;
                }
            if (flag)
                add(i, j + n, min(effort[j], effort[i])), add(j + n, i, 0);
        }
    }
    cnt = num;
    for (int i = 1; i <= n; ++i)
        add(i, i + n, inf), add(i + n, i, inf);
    for (int i = 1; i <= n; ++i)
    {
        bool flag = true;
        for (int j = 1; j <= p; ++j)
            if (in[i][j] == 1)
                flag = false;
        if (flag)
        {
            add(st, i, effort[i]), add(i, st, 0);
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        bool flag = true;
        for (int j = 1; j <= p; ++j)
            if (!out[i][j])
                flag = false;
        if (flag)
            add(i + n, ed, effort[i]), add(ed, i + n, 0);
    }
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
    {
        routenum++;
        return flow;
    }
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
        depth[st] = 2 * n + 2;
    gap[++depth[now]]++;
    return sum;
}
int ISAP()
{
    bfs();
    int ans = 0;
    while (depth[st] < 2 * n + 2)
    {
        memcpy(cur, first, sizeof(first));
        ans += dfs(st, inf);
    }
    return ans;
}
int main()
{
    while (cin >> p >> n)
    {
        init();
        st = 0, ed = 2 * n + 1;
        for (int i = 1; i <= n; ++i)
        {
            cin >> effort[i];
            for (int j = 1; j <= p; ++j)
                cin >> in[i][j];
            for (int j = 1; j <= p; ++j)
                cin >> out[i][j];
        }
        build();
        int maxflow = ISAP();
        int sum = 0;
        for (int i = 3; i <= cnt; i += 2)
        {
            if (w[i])
            {
                s.push(w[i]);
                s.push(u[i] - n);
                s.push(v[i]);
                sum++;
            }
        }
        cout << maxflow << ' ' << sum << endl;
        for (int i = 1; i <= sum; ++i)
        {
            for (int j = 1; j <= 3; ++j)
            {
                cout << s.top() << ' ';
                s.pop();
            }
            cout << endl;
        }
    }
    return 0;
}
//poj3436