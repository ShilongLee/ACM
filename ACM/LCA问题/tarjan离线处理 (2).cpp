#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
const int N=50005;
const int Q=70005;
int v[N<<2],w[N<<2],first[N<<2],ext[N<<2],num;
int rt[N];
int vis[N];
int dis[N];
vector<int >ve[N];
map<int,map<int,int > >mp;
int n,m;
int qx[Q<<2],qy[Q<<2];
void init()
{
    memset(first,-1,sizeof(first));
    memset(vis,0,sizeof(vis));
    memset(dis,0,sizeof(dis));
    num=0;
    mp.clear();
    for(int i=1; i<=n; ++i)
        rt[i]=i;
    for(int i=1; i<=n; ++i)
        ve[i].clear();
}
void add(int x,int y,int z)
{
    v[++num]=y;
    w[num]=z;
    ext[num]=first[x];
    first[x]=num;
}
int fin(int x)
{
    if(rt[x]==x)
        return x;
    return rt[x]=fin(rt[x]);
}
void tarjan(int pre,int st)
{
    for(int i=first[st]; i!=-1; i=ext[i])
    {
        int p=v[i];
        if(p==pre)
            continue;
        dis[p]=dis[st]+w[i];
        if(!vis[p])
            tarjan(st,p);
        rt[p]=st;
        vis[p]=1;
    }
    for(int i=0; i<ve[st].size(); ++i)
        if(vis[ve[st][i]])
            mp[st][ve[st][i]]=mp[ve[st][i]][st]=dis[st]+dis[ve[st][i]]-2*dis[fin(ve[st][i])];
}
int main()
{
    int k=0;
    while(~scanf("%d",&n))
    {
        init();
        for(int i=1; i<=n-1; ++i)
        {
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            add(x,y,z);
            add(y,x,z);
        }
        scanf("%d",&m);
        if(k++ != 0) 		//注意格式
        {
            printf("\n");
        }
        for(int i=1; i<=m; ++i)
        {
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            ve[x].push_back(y);
            ve[x].push_back(z);
            ve[y].push_back(x);
            ve[y].push_back(z);
            ve[z].push_back(x);
            ve[z].push_back(y);
            qx[3*(i-1)]=x;
            qy[3*(i-1)]=y;
            qx[3*(i-1)+1]=x;
            qy[3*(i-1)+1]=z;
            qx[3*(i-1)+2]=y;
            qy[3*(i-1)+2]=z;
        }
        tarjan(0,0);
        for(int i=1; i<=m; ++i)
        {
            int ans=mp[qx[3*(i-1)]][qy[3*(i-1)]]+mp[qx[3*(i-1)+1]][qy[3*(i-1)+1]]+mp[qx[3*(i-1)+2]][qy[3*(i-1)+2]];
            printf("%d\n",ans/2);
        }
    }
}
//zoj3195
