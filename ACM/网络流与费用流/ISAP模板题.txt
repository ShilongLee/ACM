/*二分多重匹配  poj3189  */

/*题意：
n(1<=n<=1000)只牛 ， b(1<=b<=20)个牛棚 ， 每个牛棚只能装一定数量的牛， 每只牛对每个牛棚按喜欢程度有自己的排名，
问怎么安排能把所有的牛安排进牛棚，并且使全局（全牛棚）的喜好度差值最小，输出最小的差值。
输入
第一行 n,b
剩下n行 每行b个数为每个牛心中的牛棚排名
最后一行 b个数代表每个牛棚的容量
输出
所有牛棚喜好度最小差值
*/

/*
我的思路：
用ISAP求二分多重匹配
源点到牛建边流量为1,牛到牛棚建边流量为1，牛棚到汇点建边流量为牛棚的容量。
然后二分差值。
*/

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;
const int N = 1005;//牛
const int B = 25;//棚
const int NODE = N + B;//总共节点数
const int M = N * B * 2 + 2 * (N + B);//边数
const int inf = 0x3f3f3f3f;
int n, b, mapp[N][B], limit[B], mid, st, ed, v[M], w[M], first[M], ext[M], num, depth[NODE], gap[NODE], cur[M], buildsum;
//st=0源点 ed=n+b+1汇点  v,w,first,ext,num链向星五件套  buildsum我测试用的主要想看看建了多少次图 
void add(int x, int y, int z)//加边
{
    v[++num] = y;
    w[num] = z;
    ext[num] = first[x];
    first[x] = num;
}
void addedge(int l, int r)//建图
{
    buildsum++;
    memset(first, -1, sizeof(first));
    num = 1;
    for (int i = 1; i <= n; ++i)
    {
        add(st, i, 1), add(i, st, 0);
        for (int j = l; j <= r; ++j)
        {
            int p = mapp[i][j];
            add(i, p + n, 1), add(p + n, i, 0);
        }
    }
    for (int i = 1; i <= b; ++i)
        add(n + i, ed, limit[i]), add(ed, n + i, 0);
}
void bfs()//从汇点逆向搜出深度
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
int dfs(int now, int flow)//isap深搜
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
        depth[st] = n + b + 2;/** 因为这里的st和循环里的st混了好久 一直TLE 把循环里的st改成now就好了*/
    gap[++depth[now]]++;
    return sum;
}
bool ISAP()
{
    for (int i = 1; i + mid - 1 <= b; ++i)//滑动窗口,窗口大小为mid
    {
        addedge(i, i + mid - 1);//建图
        bfs();//跑深度
        int ans = 0;//最后得出的最大流量
        while (depth[st] < n + b + 2)
        {
            memcpy(cur, first, sizeof(first));//当前弧优化
            ans += dfs(st, inf);
        }
        if (ans == n)
            return true;
    }
    return false;
}
int main()
{
    //cin >> n >> b;
    scanf("%d%d", &n, &b);
    st = buildsum = 0, ed = n + b + 1;  //源点0 汇点n+b+1
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= b; ++j)
            scanf("%d", &mapp[i][j]);  //牛对牛棚的排名
    //cin >> mapp[i][j];
    for (int i = 1; i <= b; ++i)
        scanf("%d", &limit[i]);       //每个牛棚装牛数量的限制
    //cin >> limit[i];
    int l = 1, r = b;//二分
    while (l <= r)
    {
        mid = (l + r) >> 1;
        if (ISAP())
            r = mid - 1;
        else
            l = mid + 1;
    }
    //cout << "buildsum=" << buildsum << endl;
    cout << l << endl;
    return 0;
}
//poj3189