#include<iostream>
#include<string.h>
#include<queue>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
const int M=500005;
int dis[N];
int /*u[M],*/v[M],w[M],first[M],ext[M];//u[i]-->v[i]=w[i]  first记录第i个节点的第一条边，ext记录每条边的下一条边
int num=0;
int n,m,s;
void add(int x,int y,int z)
{
    v[++num]=y;
    w[num]=z;
    ext[num]=first[x];
    first[x]=num;
}
void spfa(int s)
{
    for(int i=1; i<=n; ++i)
        dis[i]=inf;
    int vis[N];
    dis[s]=0;
    vis[s]=1;
    memset(vis,0,sizeof(vis));
    queue<int>qu;
    qu.push(s);
    while(!qu.empty())
    {
        int f=qu.front();
        qu.pop();
        vis[f]=0;
        for(int i=first[f]; i!=-1; i=ext[i])
        {
            int y=v[i];
            int l=w[i];
            if(dis[y]>dis[f]+l)
            {
                dis[y]=dis[f]+l;
                if(!vis[y])
                {
                    qu.push(y);
                    vis[y]=1;
                }
            }
        }
    }
}
int main()
{
    memset(first,-1,sizeof(first));
    cin>>n>>m>>s;
    for(int i=1; i<=m; ++i)
    {
        int x,y,z;
        cin>>x>>y>>z;
        add(x,y,z);
    }
    spfa(s);
    for(int i=1; i<=n; ++i)
        if(dis[i]==0x3f3f3f3f)
            cout<<(1<<31)-1<<' ';
        else
            cout<<dis[i]<<' ';
}
//  ext[ext[first[1]]]     ext[first[1]]        first[1]
//              |                      |                     |
//[1]------------>[0]-------------->[2]--------->[3]


//洛谷P3371
