#include<iostream>
#include<string.h>
#include<queue>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=30;
const int M=1005;
int dis[N];
int vis[N];
int v[M],w[M],first[M],next[M],num;
void add(int x,int y,int z)
{
    v[++num]=y;
    w[num]=z;
    next[num]=first[x];
    first[x]=num;
}
typedef pair<int,int>pii;
int n;
int Prim(int st)
{
    int sum=0;
    memset(dis,inf,sizeof(dis));
    dis[st]=0;
    memset(vis,0,sizeof(vis));
    priority_queue<pii,vector<pii>,greater<pii> >qu;
    qu.push(make_pair(0,st));
    while(!qu.empty())
    {
        pii p=qu.top();
        qu.pop();
        if(vis[p.second])
            continue;
        vis[p.second]=1;
        sum+=p.first;
        for(int i=first[p.second];i!=-1;i=next[i])
        {
            int pos=v[i];
            if(!vis[pos]&&dis[pos]>w[i])
            {
                dis[pos]=w[i];
                    qu.push(make_pair(w[i],pos));
            }
        }
    }
    return sum;
}
int main()
{
    while(cin>>n&&n)
    {
        memset(first,-1,sizeof(first));
        num=0;
        char c;
        int k,cost;
        for(int i=1;i<=n-1;++i)
        {
            cin>>c>>k;
            for(int j=1;j<=k;++j)
            {
                cin>>c>>cost;
                add(i,c-'A'+1,cost);
                add(c-'A'+1,i,cost);
            }
        }
        cout<<Prim(1)<<endl;
    }
}
//poj1251