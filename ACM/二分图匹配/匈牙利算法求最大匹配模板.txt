#include<iostream>
#include<algorithm>
#include<vector>
#include<string.h>
using namespace std;
const int N=505;
const int M=505;
int n,m,e,sum=0;
bool vis[M];
int p[M];
vector<int>ve[N];
bool match(int x)
{
    int siz=ve[x].size();
    for(int i=0; i<siz; ++i)
    {
        int y=ve[x][i];
        if(!vis[y])
        {
            vis[y]=true;
            if(!p[y]||match(p[y]))
            {
                p[y]=x;
                return true;
            }
        }
    }
    return false;
}
int main()
{
    memset(p,0,sizeof(p));
    cin>>n>>m>>e;
    for(int i=1; i<=e; ++i)
    {
        int x,y;
        cin>>x>>y;
        ve[x].push_back(y);
    }
    for(int i=1; i<=n; ++i)
    {
        memset(vis,false,sizeof(vis));
        if(match(i))
            sum++;
    }
    cout<<sum<<endl;
    return 0;
}
//洛谷p3386
