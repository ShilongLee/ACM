#include<iostream>
#include<string.h>
#include<queue>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=55;
const int M=N*N;
typedef pair<int,int>pii;
int n,m,k,a,b;
int vz[M],wz[M],firstz[M],extz[M],numz;
int vf[M],wf[M],firstf[M],extf[M],numf;
int dis[N];
struct node
{
    int u;
    long long cost;
    vector<int>path;
    node(int a,int b)
    {
        u=a;
        cost=b;
    }
    bool operator<(const node &a) const
    {
        return cost+dis[u]>a.cost+dis[a.u];
    }
};
void zadd(int x,int y,int z)
{
    vz[++numz]=y;
    wz[numz]=z;
    extz[numz]=firstz[x];
    firstz[x]=numz;
}
void fadd(int x,int y,int z)
{
    vf[++numf]=y;
    wf[numf]=z;
    extf[numf]=firstf[x];
    firstf[x]=numf;
}
void dij(int st)
{
    memset(dis,inf,sizeof(dis));
    dis[st]=0;
    bool vis[N];
    memset(vis,false,sizeof(vis));
    priority_queue<pii,vector<pii>,greater<pii> >qu;
    qu.push(make_pair(0,st));
    while(!qu.empty())
    {
        pii f=qu.top();
        qu.pop();
        if(vis[f.second])
            continue;
        vis[f.second]=1;
        for(int i=firstf[f.second]; i!=-1; i=extf[i])
        {
            int pos=vf[i];
            if(!vis[pos]&&dis[pos]>dis[f.second]+wf[i])
            {
                dis[pos]=dis[f.second]+wf[i];
                qu.push(make_pair(dis[pos],pos));
            }
        }
    }
}
node bfs(int st)
{
//    int cost=0;
    priority_queue<node>qu;
    node a(st,0);
//    a.path.push_back(st);
    qu.push(a);
    while(!qu.empty())
    {
        node f=qu.top();
        qu.pop();

        if(f.u==b/*&&f.cost!=cost*/)
        {

            k--;
//            cost=f.cost;
            if(k==0)
                return f;
        }
        for(int i=firstz[f.u]; i!=-1; i=extz[i])
        {
            node a(vz[i],f.cost+wz[i]);
//            a.path=f.path;
//            a.path.push_back(vz[i]);
            qu.push(a);
        }
    }
    return node(-1,-1);
}
int main()
{
    cin>>n>>m>>k>>a>>b;
    int u,v,l;
    numz=numf=0;
    memset(firstf,-1,sizeof(firstf));
    memset(firstz,-1,sizeof(firstz));
    for(int i=1; i<=m; ++i)
    {
        cin>>u>>v>>l;
        zadd(u,v,l);
        fadd(v,u,l);
    }
    dij(b);
    if(dis[a]==inf)
    {
        cout<<-1<<endl;
        return 0;
    }
    if(a==b)
        ++k;
    node ans=bfs(a);
    if(ans.cost==-1)
        cout<<"No"<<endl;
    else
    {
        cout<<ans.cost<<endl;
//        for(vector<int>::iterator it=ans.path.begin(); it!=ans.path.end(); it++)
//        {
//            cout<<*it;
//            if(it!=ans.path.end()-1)
//                cout<<'-';
//        }
//        cout<<endl;
    }
    return 0;
}
