#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
const int N=1005;
int n,m,vis[N],master[N],sum,mapp[N][N];
bool match(int x)
{
    for(int y=1; y<=n; ++y)
    {
        if(!vis[y]&&mapp[x][y])
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
void floyd()
{
    for(int k=1; k<=n; ++k)
        for(int i=1; i<=n; ++i)
            for(int j=1; j<=n; ++j)
                if(mapp[i][k]&&mapp[k][j])
                    mapp[i][j]=1;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    while(cin>>n>>m&&(n||m))
    {
        memset(vis,0,sizeof(vis));
        memset(master,0,sizeof(master));
        memset(mapp,0,sizeof(mapp));
        sum=0;
        for(int i=1; i<=m; ++i)
        {
            int x,y;
            cin>>x>>y;
            mapp[x][y]=1;
        }
        floyd();
        for(int i=1; i<=n; ++i)
        {
            memset(vis,0,sizeof(vis));
            if(match(i))
                sum++;
        }
        cout<<n-sum<<endl;
    }
    return 0;
}
//poj 2594
