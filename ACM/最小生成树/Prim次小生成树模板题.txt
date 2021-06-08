#include<iostream>
#include<string.h>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=110;
const int M=N*N;
int rt[N];
int vis[N];
int mapp[N][N];
int dis[N];
int path[N][N];
int used[N][N];
int n,m;
int Prim(int st)
{
    for(int i=1; i<=n; ++i)
    {
        dis[i]=mapp[i][1];
        rt[i]=1;
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
        for(int j=1; j<=n; ++j)
        {
            if(vis[j]&&j!=k)
                path[j][k]=path[k][j]=max(dis[k],path[rt[k]][j]);
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
    for(int i=1; i<=n; ++i)
        for(int j=1; j<=n; ++j)
            if(i!=j&&!used[i][j])
                ans=min(ans,x-path[i][j]+mapp[i][j]);
    return ans;
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        memset(mapp,inf,sizeof(mapp));
        memset(vis,0,sizeof(vis));
        memset(path,0,sizeof(path));
        memset(used,0,sizeof(used));
        cin>>n>>m;
        for(int i=1; i<=m; ++i)
        {
            int x,y,z;
            cin>>x>>y>>z;
            mapp[x][y]=mapp[y][x]=z;
        }
        int ans=Prim(1);
        bool p=false;
         for(int i=1; i<=n; ++i)
        for(int j=1; j<=n; ++j)
            if(i!=j&&!used[i][j]&&mapp[i][j]!=inf)
                if(path[i][j]==mapp[i][j])
                    p=true;
        if(!p)
            cout<<ans<<endl;
        else
            cout<<"Not Unique!"<<endl;
    }
    return 0;
}
//poj1679
//Prim次小生成树模板题
