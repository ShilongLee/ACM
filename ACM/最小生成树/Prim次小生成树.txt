#include<iostream>
#include<string.h>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=105;
int mapp[N][N];
int vis[N];
int dis[N];
int n,m;
int used[N][N];
int path[N][N];
int rt[N];
int Prim(int st)
{
    for(int i=1; i<=n; ++i)
    {
        rt[i]=1;
        dis[i]=mapp[i][1];
    }
    vis[st]=1;
    int ans=0;
    for(int i=1; i<=n-1; ++i)
    {
        int Min=inf,k;
        for(int j=1; j<=n; ++j)
        {
            if(!vis[j]&&dis[j]<Min)
            {
                Min=dis[j];
                k=j;
            }
        }
        vis[k]=1;
        ans+=Min;
        used[k][rt[k]]=used[rt[k]][k]=1;
        for(int j=1;j<=n;++j)
        {
            if(vis[j]&&j!=k)
                path[j][k]=path[k][j]=max(dis[k],path[j][rt[k]]);
                if(!vis[j]&&dis[j]>mapp[k][j])
                {
                    dis[j]=mapp[k][j];
                    rt[j]=k;
                }
        }
    }
    return ans;
}
int SecPrim(int x)
{
    int ans=inf;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
        if(i!=j&&!used[i][j])
        ans=min(ans,x-path[i][j]+mapp[i][j]);
    return ans;
}
int main()
{
    while(cin>>n>>m)
    {
        memset(used,0,sizeof(used));
        memset(vis,0,sizeof(vis));
        memset(mapp,inf,sizeof(mapp));
        memset(path,0,sizeof(path));
        for(int i=1; i<=m; ++i)
        {
            int x,y,z;
            cin>>x>>y>>z;
            mapp[x][y]=mapp[y][x]=z;
        }
        int ans=Prim(1);
        cout<<"最小生成树:"<<endl;
        cout<<ans<<endl;
        cout<<"次小生成树"<<endl;
        cout<<SecPrim(ans)<<endl;
    }
    return 0;
}

