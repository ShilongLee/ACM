#include <iostream>
#include <string.h>
#include <queue>
using namespace std;
const int N = 255;
const int M = N * N << 1;
int n, x, y, ans, pre[N], col[N], rt[N], v[M], first[M], ext[M], num, cnt, vis[N], like[N];
void init()
{
    memset(like, 0, sizeof(like));
    memset(vis, 0, sizeof(vis));
    memset(first, -1, sizeof(first));
    ans = cnt = 0;
    num = 1;
}
void add(int x, int y)
{
    v[++num] = y;
    ext[num] = first[x];
    first[x] = num;
}
int fin(int x)
{
    if (rt[x] == x)
        return x;
    return rt[x] = fin(rt[x]);
}
void aug(int v)
{
    int t;
    while (v)
    {
        t = like[pre[v]];
        like[v] = pre[v];
        like[pre[v]] = v;
        v = t;
    }
}
int LCA(int x, int y)
{
    ++cnt;
    x = fin(x);
    y = fin(y);
    while (vis[x] != cnt)
    {
        vis[x] = cnt;
        x = fin(pre[like[x]]);
        if (y)
            swap(x, y);
    }
    return x;
}
void shrink(int x, int y, int lca, queue<int> &q)
{
    while (fin(x) != lca)
    {
        pre[x] = y;
        y = like[x];
        if (col[y] == 2)
        {
            col[y] = 1;
            q.push(y);
        }
        if (fin(x) == x)
            rt[x] = lca;
        if (fin(y) == y)
            rt[y] = lca;
        x = pre[y];
    }
}
bool bfs(int st)
{
    queue<int> q;
    q.push(st);
    while (!q.empty())
    {
        int f = q.front();
        q.pop();
        for (int i = first[f]; ~i; i = ext[i])
        {
            int p = v[i];
            if (!col[p])
            {
                pre[p] = f;
                if (!like[p])
                {
                    aug(p);
                    return true;
                }
                else
                {
                    col[p] = 2;
                    col[like[p]] = 1;
                    q.push(like[p]);
                }
            }
            else
            {
                if (fin(p) == fin(f))
                    continue;
                if (col[p] == 1)
                {
                    int lca = LCA(f, p);
                    shrink(p, f, lca, q);
                    shrink(f, p, lca, q);
                }
            }
        }
    }
    return false;
}
bool blossom(int st)
{
    memset(pre, 0, sizeof(pre));
    memset(col, 0, sizeof(col));
    for (int i = 1; i <= n; ++i)
        rt[i] = i;
    col[st] = 1;
    if (bfs(st))
        return true;
    else
        return false;
}
int main()
{
    cin >> n;
    init();
    while (cin >> x >> y)
    {
        if (!like[x] && !like[y])
        {
            like[x] = y;
            like[y] = x;
            ans++;
        }
        add(x, y);
        add(y, x);
    }
    for (int i = 1; i <= n; ++i)
        if (!like[i] && blossom(i))
            ans++;
    cout << ans * 2 << endl;
    for (int i = 1; i <= n; ++i)
        if (i < like[i])
            cout << i << ' ' << like[i] << endl;
    return 0;
}
//URAL1099