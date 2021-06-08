#include<iostream>
#include<queue>
#include<stdio.h>
#include<string.h>
using namespace std;
const int N=1000005;
const long long inf=0x3f3f3f3f3f3f3f3f;
int v1[N],first1[N],next1[N],num1;
int v2[N],first2[N],next2[N],num2;
int w1[N],w2[N];
int n,m;
long long  dis1[N];
long long  dis2[N];
void add1(int x,int y,int  z)
{
    v1[++num1]=y;
    w1[num1]=z;
    next1[num1]=first1[x];
    first1[x]=num1;
}
void add2(int x,int y,int z)
{
    v2[++num2]=x;
    w2[num2]=z;
    next2[num2]=first2[y];
    first2[y]=num2;
}
void dij1(int st)
{
    for(int i=1; i<=n; ++i)
        dis1[i]=inf;
    dis1[st]=0;
    int vis[N];
    memset(vis,0,sizeof(vis));
    priority_queue<pair<long long,long long>,vector<pair<long long,long long> >,greater< pair<long long,long long> > >qu;
    qu.push(make_pair(0,st));
    while(!qu.empty())
    {
        int p=qu.top().second;
        qu.pop();
        if(vis[p])
            continue;
        vis[p]=1;
        for(int i=first1[p]; i!=-1; i=next1[i])
        {
            if(!vis[v1[i]])
            {
                dis1[v1[i]]=min(dis1[v1[i]],dis1[p]+w1[i]);
                qu.push(make_pair(dis1[v1[i]],v1[i]));
            }
        }
    }
}
void dij2(int st)
{
    for(int i=1; i<=n; ++i)
        dis2[i]=inf;
    dis2[st]=0;
    int vis[N];
    memset(vis,0,sizeof(vis));
    priority_queue<pair<long long,long long>,vector<pair<long long,long long> >,greater< pair<long long,long long> > >qu;
    qu.push(make_pair(0,st));
    while(!qu.empty())
    {
        int p=qu.top().second;
        qu.pop();
        if(vis[p])
            continue;
        vis[p]=1;
        for(int i=first2[p]; i!=-1; i=next2[i])
        {
            if(!vis[v2[i]])
            {
                dis2[v2[i]]=min(dis2[v2[i]],dis2[p]+w2[i]);
                qu.push(make_pair(dis2[v2[i]],v2[i]));
            }
        }
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        num1=0;
        num2=0;
        memset(first1,-1,sizeof(first1));
        memset(first2,-1,sizeof(first2));
        scanf("%d%d",&n,&m);
        for(int i=1; i<=m; ++i)
        {
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            add1(x,y,z);
            add2(x,y,z);
        }
        dij1(1);
        dij2(1);
        long long sum=0;
        for(int i=1; i<=n; ++i)
        {
            sum+=dis1[i];
            sum+=dis2[i];
        }
        printf("%lld\n",sum);
    }
    return 0;
}
//poj1511