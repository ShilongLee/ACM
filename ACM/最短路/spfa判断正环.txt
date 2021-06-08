#include<iostream>
#include<string.h>
#include<queue>
using namespace std;
const int N=105;
const int M=505;
const double inf=0x3f3f3f3f;
int n,m,st;
double mo;
double dis[N];
int v[M],first[M],next[M],num;
struct ex
{
    double cost,rate;
} w[M];
void add(int a,int b,double c,double d)
{
    v[++num]=b;
    w[num].rate=c;
    w[num].cost=d;
    next[num]=first[a];
    first[a]=num;
}
bool spfs(int st,double mo)
{
    memset(dis,0,sizeof(dis));
    dis[st]=mo;
    int vis[N];
    memset(vis,0,sizeof(vis));
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
            if(dis[pos]<(dis[f]-w[i].cost)*w[i].rate)
            {
                dis[pos]=(dis[f]-w[i].cost)*w[i].rate;
                if(!vis[pos])
                {
                    vis[pos]=1;
                    qu.push(pos);
                }
                cnt[pos]=cnt[f]+1;
            }
            if(cnt[pos]>=n) return true;
        }
    }
    return false;
}
int main()
{
    memset(first,-1,sizeof(first));
    cin>>n>>m>>st>>mo;
    num=0;
    for(int i=1; i<=m; ++i)
    {
        int a,b;
        double c,d,e,f;
        cin>>a>>b>>c>>d>>e>>f;
        add(a,b,c,d);
        add(b,a,e,f);
    }
    cout<<(spfs(st,mo)?"YES":"NO")<<endl;
}
//poj1860