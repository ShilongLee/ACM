#include <stdio.h>
#include <string.h>
#include <queue>
#include<functional>
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 1055;
const int M = 200005;
const int inf = 0x3f3f3f3f;
typedef pair<int, int> pii;
int n, m, v[M], w[M], first[M], ext[M], num, st, ed, dis1[N], dis2[N], depth[N], gap[N], node, cur[M];
int v2[M], w2[M], ext2[M], first2[M], num2;
int v0[M], w0[M], ext0[M], first0[M], num0;
bool vis[N];
void add(int x, int y, int z)
{
	v[++num] = y;
	w[num] = z;
	ext[num] = first[x];
	first[x] = num;
}
void add2(int x, int y, int z)
{
	v2[++num2] = y;
	w2[num2] = z;
	ext2[num2] = first2[x];
	first2[x] = num2;
}
void add0(int x, int y, int z)
{
	v0[++num0] = y;
	w0[num0] = z;
	ext0[num0] = first0[x];
	first0[x] = num0;
}
void init()
{
	memset(first0, -1, sizeof(first0));
	memset(first, -1, sizeof(first));
	memset(first2, -1, sizeof(first2));
	num0 = num = num2 = 1;
	node = 0;
}
void dij1(int st)
{
	memset(dis1, inf, sizeof(dis1));
	memset(vis, false, sizeof(vis));
	dis1[st] = 0;
	priority_queue<pii,vector<pii>,greater<pii> > q;
	q.push(make_pair(dis1[st], st));
	while (!q.empty())
	{
		pii f = q.top();
		q.pop();
		if (vis[f.second])
			continue;
		vis[f.second] = true;
		for (int i = first[f.second]; ~i; i = ext[i])
		{
			int p = v[i];
			if (!vis[p] && dis1[p] > dis1[f.second] + w[i])
			{
				dis1[p] = dis1[f.second] + w[i];
				q.push(make_pair(dis1[p], p));
			}
		}
	}
	return;
}
void dij2(int st)
{
	memset(dis2, inf, sizeof(dis2));
	memset(vis, false, sizeof(vis));
	dis2[st] = 0;
	priority_queue<pii,vector<pii>,greater<pii> > q;
	q.push(make_pair(dis2[st], st));
	while (!q.empty())
	{
		pii f = q.top();
		q.pop();
		if (vis[f.second])
			continue;
		vis[f.second] = true;
		for (int i = first0[f.second]; ~i; i = ext0[i])
		{
			int p = v0[i];
			if (!vis[p] && dis2[p] > dis2[f.second] + w0[i])
			{
				dis2[p] = dis2[f.second] + w0[i];
				q.push(make_pair(dis2[p], p));
			}
		}
	}
	return;
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
		for (int i = first2[f]; ~i; i = ext2[i])
		{
			int p = v2[i];
			if (!depth[p] && w2[i])
			{
				depth[p] = depth[f] + 1;
				q.push(p);
			}
		}
	}
	return depth[ed];
}
int dfs(int now, int flow)
{
	if (now == ed)
		return flow;
	int sum = 0;
	for (int &i = cur[now]; ~i; i = ext2[i])
	{
		int p = v2[i];
		if (w2[i] && depth[p] == depth[now] + 1)
		{
			int t = dfs(p, min(flow, w2[i]));
			w2[i] -= t;
			w2[i ^ 1] += t;
			flow -= t;
			sum += t;
			if (!flow)
				return sum;
		}
	}
	if (!sum)
		depth[now] = 0;
	return sum;
}
int Dinic()
{
	int ans = 0;
	while (bfs())
	{
		memcpy(cur, first2, sizeof(first2));
		ans += dfs(st, inf);
	}
	return ans;
}
int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d%d", &n, &m);
		init();
		for (int i = 1; i <= m; ++i)
		{
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			add(a, b, c);
			add0(b, a, c);
		}
		scanf("%d%d", &st, &ed);
		dij1(st);
		dij2(ed);
		memset(vis, false, sizeof(vis));
		for (int i = 1; i <= n; ++i)
			for (int j = first[i]; ~j; j = ext[j])
			{
				int p = v[j];
				if (dis1[i] + dis2[p] + w[j] == dis1[ed])
					add2(i, p, 1), add2(p, i, 0);
			}
		printf("%d\n", Dinic());
	}
	return 0;
}
//hdu3416
/*开始以为是最小费用流，其实是最短路加最大流。抛开走最短的限制，那么就是裸的最大流，边权设为1，跑dinic就可以了。
关键在于如何确定哪些边是最短的。对于u->v的权为w的边，当且仅当dis1[u]+dis2[v]+w==dis1[t]时，这条边是最短路的边。用语言描述就是：从起点到u的最小距离+边权+v到终点的最小距离=起点到终点的最小距离。其中dis2[v]是通过反向建图跑反向最短路跑出来的，关于反向建图可以参考我之前的题解 POJ-3268。
那么现在思路就很清晰了，正向反向两次建图两次最短路处理出dis1和dis2两个数组，之后枚举每一条边，判断他是否是最短路内的边，如果是就加入到网络流图内。最后跑一遍dinic求出最大流就可以了。*/