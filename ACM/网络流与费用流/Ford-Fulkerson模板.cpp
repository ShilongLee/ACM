#include<string.h>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=205;
const int M=5005;
const long long inf=1e18;
int n,m,s,t,v[M<<1],first[M<<1],ext[M<<1],num;
long long w[M<<1];
bool vis[N];
void add(int x,int y,long long z)
{
    v[++num]=y;
    w[num]=z;
    ext[num]=first[x];
    first[x]=num;
}
long long dfs(int st,long long flow)
{
    if(st==t)
        return flow;
    vis[st]=true;
    for(int i=first[st]; ~i; i=ext[i])
    {
        int p=v[i];
        if(!vis[p]&&w[i])
        {
            int t=dfs(p,min(flow,w[i]));
            if(t>0)
            {
                w[i]-=t;
                w[i^1]+=t;
                return t;
            }
        }
    }
    return 0;
}
int main()
{
    memset(first,-1,sizeof(first));
    num=1;
    cin>>n>>m>>s>>t;
    for(int i=1; i<=m; ++i)
    {
        int x,y,z;
        cin>>x>>y>>z;
        add(x,y,z);
        add(y,x,0);
    }
    long long res=0,ans=0;
    while(memset(vis,false,sizeof(vis))&&(res=dfs(s,inf))>0)
    {
        ans+=res;
    }
    cout<<ans<<endl;
    return 0;
}
//洛谷3376
