#include<iostream>
#include<string.h>
#include<vector>
#include<queue>
using namespace std;
const int inf=0x3f3f3f3f;
const int minf=-0x3f3f3f3f;
const int N=105;
int u[N],v[N],w[N],dis[N];//u[i]-->v[i]=w[i] dis[]是各个点到源点的距离
int n,m;
int main()
{
    cin>>n>>m;
    for(int i=1; i<=m; ++i)
        cin>>u[i]>>v[i]>>w[i];
    memset(dis,inf,sizeof(dis));
    dis[1]=0;
    for(int i=1; i<=n-1; ++i)
        for(int j=1; j<=m; ++j)
            dis[v[j]]=min(dis[v[j]],dis[u[j]]+w[j]);
    for(int i=1; i<=n; ++i)
        cout<<dis[i]<<' ';
    cout<<endl;
    for(int i=1; i<=n-1; ++i)
        for(int j=1; j<=m; ++j)
            if(dis[v[j]]>dis[u[j]]+w[j])
                dis[v[j]]=minf;
    for(int i=1; i<=n; ++i)
        cout<<dis[i]<<' ';
    cout<<endl;
}
