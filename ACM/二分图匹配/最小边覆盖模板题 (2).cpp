#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
const int N=1005;
int n,m,v[N*N],first[N*N],ext[N*N],num,vis[N],master[N],sum;
void add(int x,int y)
{
    v[++num]=y;
    ext[num]=first[x];
    first[x]=num;
}
bool match(int x)
{
    for(int i=first[x];~i;i=ext[i])
    {
        int y=v[i];
        if(!vis[y])
        {
            vis[y]=true;
            if(!master[y]||match(master[y]))
            {
                master[y]=x;
                return true;
            }
        }
    }
    return false;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--)
    {
        memset(first,-1,sizeof(first));
        memset(vis,0,sizeof(vis));
        memset(master,0,sizeof(master));
        num=sum=0;
        cin>>n>>m;
        for(int i=1;i<=m;++i)
        {
            int x,y;
            cin>>x>>y;
            add(x,y);
        }
        for(int i=1;i<=n;++i)
        {
            memset(vis,0,sizeof(vis));
            if(match(i))
                sum++;
        }
        cout<<n-sum<<endl;
    }
}
//hdu1151
//两边没有关系，因为匹配过的点可以继续用。