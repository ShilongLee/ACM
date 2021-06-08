#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
const int N=105;
const int M=N*N;
const int inf=0x3f3f3f3f;
int n,m;
int v[M],w[M],first[M],ext[M],num;
int rt[N];
struct node
{
    int x,y,len;
} edge[M];
int vis[M];
int dis1[N][N];
int dis2[N][N];
void add(int x,int y,int z)
{
    v[++num]=y;
    w[num]=z;
    ext[num]=first[x];
    first[x]=num;
}
int fin(int x)
{
    return rt[x]==x?x:(rt[x]=fin(rt[x]));
}
bool cmp(node a,node b)
{
    return a.len<b.len;
}
void dfs(int st,int rt,int md1,int md2,int d1[],int d2[])
{
    d1[st]=md1;
    d2[st]=md2;
    for(int i=first[st]; i!=-1; i=ext[i])
    {
        int j=v[i];
        if(j!=rt)
        {
            int t1=md1,t2=md2;
            if(w[i]>md1)
                t2=t1,t1=w[i];
            else if(w[i]<t1&&w[i]>t2)
                t2=w[i];
            dfs(j,st,t1,t2,d1,d2);
        }
    }
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        memset(first,-1,sizeof(first));
        num=0;
        cin>>n>>m;
        for(int i=1; i<=n; ++i)
            rt[i]=i;
        for(int i=1; i<=m; ++i)
        {
            int x,y,z;
            cin>>x>>y>>z;
            edge[i].x=x;
            edge[i].y=y;
            edge[i].len=z;
        }
        sort(edge+1,edge+1+m,cmp);
        long long sum=0;
        for(int i=1; i<=m; ++i)
        {
            int xx=fin(edge[i].x);
            int yy=fin(edge[i].y);
            if(xx!=yy)
            {
                sum+=edge[i].len;
                vis[i]=1;
                rt[xx]=yy;
                add(edge[i].x,edge[i].y,edge[i].len);
                add(edge[i].y,edge[i].x,edge[i].len);
            }
        }
        long long res=inf;
        for(int i=1; i<=n; ++i)
            dfs(i,-1,0,0,dis1[i],dis2[i]);
        for(int i=1; i<=m; ++i)
        {
            if(!vis[i])
            {
                int x=edge[i].x,y=edge[i].y,len=edge[i].len;
                if(len>dis1[x][y])
                    res=min(res,sum+len-dis1[x][y]);
                else if(len>dis2[x][y])
                    res=min(res,sum+len-dis2[x][y]);
            }
        }
        cout<<res<<endl;
    }
    return 0;
}
//ACwing 1148
//严格次小生成树要记录i~j的最大边和次大边