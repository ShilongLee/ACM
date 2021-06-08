#include<iostream>
#include<string.h>
#include<queue>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=505;
const int M=10005;
int v[M],w[M],first[M],next[M];
int num;
int n,m,W;
int dis[N];
void add(int x,int y,int z)
{
    v[++num]=y;
    w[num]=z;
    next[num]=first[x];
    first[x]=num;
}
bool spfa(int st)
{
    int cnt[N];
    memset(cnt,0,sizeof(cnt));
    memset(dis,inf,sizeof(dis));
    dis[st]=0;
    int vis[N];
    memset(vis,0,sizeof(vis));
    vis[st]=1;
    cnt[st]++;
    queue<int>qu;
    qu.push(st);
    while(!qu.empty())
    {
        int f=qu.front();
        qu.pop();
        vis[f]=0;
        for(int i=first[f]; i!=-1; i=next[i])
        {
            int pos=v[i];
            if(dis[pos]>dis[f]+w[i])
            {
                dis[pos]=dis[f]+w[i];
                if(!vis[pos])
                {
                    vis[pos]=1;
                    qu.push(pos);
                }
                cnt[pos]=cnt[f]+1;
            }
            if(cnt[pos]>n)
                return true;
        }
    }
    return false;
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        memset(first,-1,sizeof(first));
        num=0;
        cin>>n>>m>>W;
        for(int i=1; i<=m; ++i)
        {
            int x,y,z;
            cin>>x>>y>>z;
            add(x,y,z);
            add(y,x,z);
        }
        for(int i=1; i<=W; ++i)
        {
            int x,y,z;
            cin>>x>>y>>z;
            add(x,y,-z);
        }
        cout<<(spfa(1)?"YES":"NO")<<endl;
    }
}
//poj3259

//首先我们要知道，对于一个不存在负环的图，从起点到任意一个点最短距离经过的点最多只有 n 个
//
//这样的话，我们用 cnt[ i ] 表示从起点（假设就是 1）到 i 的最短距离包含点的个数，初始化 cnt[ 1 ] = 1，那么当我们能够用点 u 松弛点 v 时，松弛时同时更新 cnt[ v ] = cnt[ u ] + 1，若发现此时 cnt[ v ] > n，那么就存在负环
