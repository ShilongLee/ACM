#include<iostream>
#include<string.h>
using namespace std;
const int inf=0x3f3f3f3f;
int dis[1005];
int mapp[1005][1005];
int vis[1005];
int t,n;
void diss(int s,int e)
{
    memset(vis,0,sizeof(vis));
    int minn,k;
    dis[s]=0;
    vis[s]=1;
    for(int i=0;i<n;++i)
        dis[i]=mapp[s][i];
    for(int i=0;i<n;++i)
    {
        minn=inf;
        for(int j=0;j<n;++j)
        {
            if(!vis[j]&&dis[j]<minn)
            {
                minn=dis[j];
                k=j;
            }
        }
        if(minn==inf) break;
        vis[k]=1;
        for(int j=0;j<n;++j)
            if(!vis[j]) dis[j]=min(dis[j],dis[k]+mapp[k][j]);
    }
    if(dis[e]==inf)
        cout<<-1<<endl;
    else cout<<dis[e]<<endl;
}
int main()
{
    while(cin>>t>>n)
    {
        for(int i=0;i<n;++i)
        {
            dis[i]=inf;
            for(int j=0;j<n;++j)
                mapp[i][j]=inf;
        }
        for(int i=0;i<t;++i)
        {
            int x,y,z;
            cin>>x>>y>>z;
            x--;
            y--;
            mapp[x][y]=mapp[y][x]=min(mapp[x][y],z);
        }
        diss(0,n-1);
    }
}

//poj 2387