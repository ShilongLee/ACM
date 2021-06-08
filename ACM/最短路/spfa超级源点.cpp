#include<iostream>
#include<string.h>
#include<queue>
using namespace std;
const int N=105;
const int M=N*N;
const int inf=0x3f3f3f3f;
int m,n;
int v[M],w[M],first[M],next[M],num;
int lev[N];
int dis[N];
void add(int x,int y,int z)
{
    v[++num]=y;
    w[num]=z;
    next[num]=first[x];
    first[x]=num;
}
void spfa(int st,int l,int r)
{
    memset(dis,inf,sizeof(dis));
    dis[st]=0;
    bool vis[N];
    memset(vis,0,sizeof(vis));
    vis[st]=1;
    queue<int>qu;
    qu.push(st);
    int cnt[N];
    memset(cnt,0,sizeof(cnt));
    cnt[st]=0;
    while(!qu.empty())
    {
        int f=qu.front();
        qu.pop();
        vis[f]=0;
        if(lev[f]<l||lev[f]>r) continue;
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
                        cnt[pos]=cnt[f]+1;
                    }
                }
                if(cnt[pos]>=n) return;
        }
    }
    return;
}
int main()
{
    cin>>m>>n;
    num=0;
    memset(first,-1,sizeof(first));
    for(int i=1; i<=n; ++i)
    {
        int P,L,X;
        cin>>P>>L>>X;
        add(1,i+1,P);
        lev[i+1]=L;
        while(X--)
        {
            int T,V;
            cin>>T>>V;
            add(T+1,i+1,V);
        }
    }
    lev[1]=lev[2];
    int ans=inf;
    for(int i=lev[2]-m; i<=lev[2]; ++i)
    {
        spfa(1,i,i+m);
        ans=min(ans,dis[2]);
    }
    cout<<ans<<endl;
}
//poj 1026 超级源点