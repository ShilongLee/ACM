#include<iostream>
#include<string.h>
#include<queue>
#include<vector>
using namespace std;
const int N=100005;
const int inf=0x3f3f3f3f;
int n,m,s;
int dis[N];
vector<pair<int,int> >v[N];
void spfa(int s)
{
    for(int i=1; i<=n; ++i)
        dis[i]=inf;
    dis[s]=0;
    int vis[N];
    memset(vis,0,sizeof(vis));
    queue<int >qu;
    vis[s]=1;
    qu.push(s);
    while(!qu.empty())
    {
        int f=qu.front();
        qu.pop();
        vis[f]=0;
        for(int i=0; i<v[f].size(); ++i)
        {
            int y=v[f][i].first;
            int w=v[f][i].second;
            if(dis[y]>dis[f]+w)
            {
                dis[y]=dis[f]+w;
                if(!vis[y])
                {
                    qu.push(y);
                    vis[y]=1;
                }
            }
        }
    }
}
int main()
{
    cin>>n>>m>>s;
    for(int i=1; i<=m; ++i)
    {
        int x,y,z;
        cin>>x>>y>>z;
        v[x].push_back(make_pair<int,int>(y,z));
    }
    /*for(int k=1; k<=n; ++k)
        for(int i=0; i<v[k].size(); ++i)
            cout<<k<<' '<<v[k][i].first<<' '<<v[k][i].second<<endl;*/
    spfa(s);
    for(int i=1; i<=n; ++i)
    if(dis[i]==inf) cout<<(1<<31)-1<<' ';
        else cout<<dis[i]<<' ';
}

//洛谷P3371