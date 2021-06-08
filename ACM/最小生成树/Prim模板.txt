#include<iostream>
#include<string.h>
using namespace std;
const int inf=0x3f3f3f3f;
int mp[105][105];
int dis[105];
int vis[105];
int main()
{
    int n,pos,Min,ans;
    cin>>n;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
    {
        cin>>mp[i][j];
        if(mp[i][j]==-1) mp[i][j]=inf;
    }
    for(int i=1;i<=n;++i)
        dis[i]=mp[i][1];
        memset(vis,0,sizeof(vis));
        vis[1]=1;
        ans=0;
        for(int i=1;i<=n-1;++i)
        {
            Min=inf;
            for(int j=1;j<=n;++j)
                if(!vis[j]&&dis[j]<Min)
            {
                pos=j;
                Min=dis[j];
            }
            vis[pos]=1;
            ans+=Min;
            for(int j=1;j<=n;++j)
                dis[j]=min(dis[j],mp[pos][j]);
        }
        cout<<ans<<endl;
        return 0;
}
//prim最小生成树算法模板