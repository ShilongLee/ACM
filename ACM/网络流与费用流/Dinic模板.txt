#include<iostream>
#include<algorithm>
#include<queue>
#include<string.h>
using namespace std;
const long long inf=1e18;
const int N=205;
const int M=10005;
int n,m,s,t,v[M],first[M],ext[M],num,depth[N];
long long w[M];
void add(int x,int y,long long z)
{
    v[++num]=y;
    w[num]=z;
    ext[num]=first[x];
    first[x]=num;
}
bool bfs(int st)
{
    memset(depth,0,sizeof(depth));
    queue<int>q;
    q.push(st);
    depth[st]=1;
    while(!q.empty())
    {
        int f=q.front();
        q.pop();
        for(int i=first[f]; ~i; i=ext[i])
        {
            int p=v[i];
            if(w[i]&&!depth[p])
            {
                depth[p]=depth[f]+1;
                q.push(p);
            }
        }
    }
    return depth[t];
}
long long dfs(int s,long long flow)
{
    if(s==t)
         return flow;
    long long sum=0;
    for(int i=first[s];~i;i=ext[i])
    {
        int p=v[i];
        if(w[i]&&depth[p]==depth[s]+1)
        {
            int t=dfs(p,min(flow,w[i]));
            w[i]-=t;
            w[i^1]+=t;
            sum+=t;
            flow-=t;
        }
    }
    if(!sum) depth[s]=0;
    return sum;
}
int main()
{
    memset(first,-1,sizeof(first));
    num=1;
    cin>>n>>m>>s>>t;
    for(int i=1; i<=m; ++i)
    {
        int x,y;
        long long z;
        cin>>x>>y>>z;
        add(x,y,z);
        add(y,x,0);
    }
    long long ans=0;
    while(bfs(s))
        ans+=dfs(s,inf);
        cout<<ans<<endl;
    return 0;
}