#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;
const int N=1005;
const int inf=0x3f3f3f3f;
int n,m;
int v[N*1000],w[N*1000],first[N*1000],next[N*1000];
int num;
int dis[N];
void add(int x,int y,int z)
{
    v[++num]=y;
    w[num]=z;
    next[num]=first[x];
    first[x]=num;
}
void dij(int s)
{
    memset(dis,inf,sizeof(dis));
    int vis[N];
    //dis[s]=0;
    memset(vis,0,sizeof(vis));
    priority_queue<pair<int,int> >qu;
    qu.push(make_pair(0,s));
    while(!qu.empty())
    {
        pair<int,int>f=qu.top();
        qu.pop();
        int p=f.second;
        if(vis[p])
            continue ;
        vis[p]=1;
        for(int i=first[p]; i!=-1; i=next[i])
            if(!vis[v[i]])
            {
                if(dis[v[i]]==inf)
                    dis[v[i]]=min(dis[p],w[i]);
                else
                    dis[v[i]]=max(dis[v[i]],min(dis[p],w[i]));
                qu.push(make_pair(dis[v[i]],v[i]));
            }
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    for(int tt=1; tt<=t; ++tt)
    {
        memset(first,-1,sizeof(first));
        num=0;
        scanf("%d%d",&n,&m);
        for(int i=1; i<=m; ++i)
        {
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            add(x,y,z);
            add(y,x,z);
        }
        dij(1);
        printf("Scenario #%d:\n",tt);
        printf("%d\n\n",dis[n]);
    }
    return 0;
}
//poj 1797
