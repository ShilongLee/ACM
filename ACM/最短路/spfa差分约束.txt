#include<iostream>
#include<stdio.h>
#include<string.h>
#include<queue>
#include<stack>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=30005;
const int M=150005;
int n,m;
int v[M],w[M],first[M],next[M],num;
int dis[N];
void add(int x,int y,int z)
{
    v[++num]=y;
    w[num]=z;
    next[num]=first[x];
    first[x]=num;
}
void spfa(int st)
{
    memset(dis,inf,sizeof(dis));
    dis[st]=0;
    bool vis[N];
    memset(vis,0,sizeof(vis));
    int cnt[N];
    memset(cnt,0,sizeof(cnt));
    vis[st]=1;
    stack<int>qu;
    qu.push(st);
    while(!qu.empty())
    {
        int f=qu.top();
        qu.pop();
        vis[f]=0;
        for(int i=first[f];i!=-1;i=next[i])
        {
            int pos=v[i];
            if(dis[pos]>dis[f]+w[i])
            {
                dis[pos]=dis[f]+w[i];
                if(!vis[pos])
                {
                    vis[pos]=1;
                    qu.push(pos);
                }
                cnt[pos]=cnt[f]+1;
            }
            if(cnt[pos]>=n) return;
        }
    }
    return;
}
int main()
{
    num=0;
    memset(first,-1,sizeof(first));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        add(a,b,c);
    }
    spfa(1);
    printf("%d\n",dis[n]);
}
//spfa解差分约束
//poj3159