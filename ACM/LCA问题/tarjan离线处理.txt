#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
const int N=40005;
const int M=205;
int n,m;
int v[N<<1],w[N<<1],first[N<<1],ext[N<<1],num;
bool vis[N];
int dis[N];
int rt[N];
int qx[M];
int qy[M];
vector<int >ve[N];
map<int,map<int,int> >mp;
int fin(int x)
{
    if(rt[x]==x)
        return x;
    return rt[x]=fin(rt[x]);
}
void add(int x,int y,int k)
{
    v[++num]=y;
    w[num]=k;
    ext[num]=first[x];
    first[x]=num;
}
void tarjan(int pre,int st)
{
    for(int i=first[st]; i!=-1; i=ext[i])
    {
        int p=v[i];
//        cout<<p<<' '<<st<<endl;
        if(p==pre)
            continue;
        dis[p]=dis[st]+w[i];
//        cout<<"dis["<<p<<"]="<<dis[p]<<endl;
        if(!vis[p])
            tarjan(st,p);
        rt[p]=st;
        vis[p]=true;
    }
    for(int i=0; i<ve[st].size(); i++)
    {
        int x=ve[st][i];
        if(vis[x])
            mp[x][st]=mp[st][x]=dis[st]+dis[x]-2*dis[fin(x)];
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        num=0;
        memset(first,-1,sizeof(first));
        memset(vis,false,sizeof(vis));
        memset(dis,0,sizeof(dis));
        scanf("%d%d",&n,&m);
        for(int i=1; i<=n; ++i)
            rt[i]=i;
        mp.clear();
        for(int i=1; i<=n; ++i)
            ve[i].clear();
        for(int i=1; i<=n-1; ++i)
        {
            int x,y,k;
           scanf("%d%d%d",&x,&y,&k);
            add(x,y,k);
            add(y,x,k);
        }
        for(int i=1; i<=m; ++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            qx[i]=x;
            qy[i]=y;
            ve[x].push_back(y);
            ve[y].push_back(x);
        }
        tarjan(1,1);
        for(int i=1; i<=m; ++i)
            printf("%d\n",mp[qx[i]][qy[i]]);
    }
}
//hdu2586
