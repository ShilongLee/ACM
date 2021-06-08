#include <iostream>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;
const int N = 3005;
const int B = 105;
const int NODE = N + B;
const int MAXM = N * B;
const int inf = 0x3f3f3f3f;
int mapp[N][B], limit[B], n, b, mid, st, ed, v[MAXM], w[MAXM], first[MAXM], ext[MAXM], num, cur[MAXM], depth[NODE];
void add(int x, int y, int z)
{
    v[++num] = y;
    w[num] = z;
    ext[num] = first[x];
    first[x] = num;
}
void addedge(int l, int r)
{
    memset(first, -1, sizeof(first));
    num = 1;
    for (int i = 1; i <= n; ++i)
    {
        add(st, i, 1), add(i, st, 0);
        for (int j = l; j <= r; ++j)
        {
            int p = mapp[i][j];
            add(i, p+n, 1), add(p+n, i, 0);
        }
    }
    for (int i = n + 1; i <= n + b; ++i)
        add(i, ed, limit[i - n]), add(ed, i, 0);
}
bool bfs()
{
    memset(depth, 0, sizeof(depth));
    depth[st] = 1;
    queue<int> q;
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
        if(w[i]&&depth[p]==depth[st]+1)
        {
            int t = dfs(p, min(w[i], flow));
            w[i] -= t;
            w[i ^ 1] += t;
            flow-=t;
            sum += t;
            if(flow==0)
                return sum;
        }
    }
    if(!sum)
        depth[st] = 0;
    return sum;
}
bool dinic()
{
    for (int i = 1; i + mid - 1 <= b; ++i)
    {
        addedge(i, i + mid - 1);
        int ans = 0,res;
        while (bfs())
        {
            memcpy(cur, first, sizeof(first));
            if(res=dfs(st,inf))
                ans += res;
            else
                break;
        }
        if (ans == n)
            return true;
    }
    return false;
}
int main()
{
    cin >> n >> b;
    st = 0, ed = n + b + 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= b; ++j)
            cin >> mapp[i][j];
    for (int i = 1; i <= b; ++i)
        cin >> limit[i];
    int l = 1, r = b;
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
//poj3189