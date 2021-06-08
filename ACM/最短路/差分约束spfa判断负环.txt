#include<iostream>
#include<string.h>
#include<queue>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1005;
const int M=60005;
int n,ml,md;
int v[M],w[M],first[M],next[M],num;
int dis[N];
void add(int x,int y,int z)
{
    v[++num]=y;
    w[num]=z;
    next[num]=first[x];
    first[x]=num;
}
bool spfa(int st)
{
    memset(dis,inf,sizeof(dis));
    dis[st]=0;
    bool vis[N];
    memset(vis,false,sizeof(vis));
    vis[st]=1;
    int cnt[N];
    memset(cnt,0,sizeof(cnt));
    queue<int>qu;
    qu.push(st);
    while(!qu.empty())
    {
        int f=qu.front();
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
            if(cnt[pos]>=n)
                return true;
        }
    }
    return false;
}
int main()
{
    num=0;
    memset(first,-1,sizeof(first));
    cin>>n>>ml>>md;
    for(int i=1;i<=ml;++i)
    {
        int a,b,c;
        cin>>a>>b>>c;
        add(a,b,c);
    }
    for(int i=1;i<=md;++i)
    {
        int a,b,c;
        cin>>a>>b>>c;
        add(b,a,-c);
    }
    if(spfa(1)) cout<<-1<<endl;
    else
    {
        if(dis[n]==inf)
            cout<<-2<<endl;
        else cout<<dis[n]<<endl;
    }
}
//spfa差分约束判断负环
//poj3169