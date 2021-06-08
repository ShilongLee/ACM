#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
const int N=105;
const int M=105;
const int K=N*M;
int n,m,k,vis[M<<2],master[M<<2],sum;
bool mapp[N][M];
bool match(int x)
{
    for(int i=1; i<=m; ++i)
    {
        if(!vis[i]&&mapp[x][i])
        {
            vis[i]=true;
            if(!master[i]||match(master[i]))
            {
                master[i]=x;
                return true;
            }
        }
    }
    return false;
}
int main()
{
    int cas=0;
    while(cin>>n>>m>>k)
    {
        sum=0;
        memset(mapp,false,sizeof(mapp));
        memset(master,0,sizeof(master));
        for(int i=1; i<=k; ++i)
        {
            int x,y;
            cin>>x>>y;
            mapp[x][y]=true;
        }
        for(int i=1; i<=n; ++i)
        {
            memset(vis,0,sizeof(vis));
            if(match(i))
                sum++;
        }
        int ans=0;
        for(int i=1; i<=n; ++i)
            for(int j=1; j<=m; ++j)
            {
                if(mapp[i][j])
                {
                    mapp[i][j]=false;
                    int num=0;
                    memset(master,0,sizeof(master));
                    for(int k=1; k<=n; ++k)
                    {
                        memset(vis,0,sizeof(vis));
                        if(match(k))
                            num++;
                    }
                    if(num!=sum)
                        ans++;
                    mapp[i][j]=true;
                }
            }
            cout<<"Board "<<++cas<<" have "<<ans<<" important blanks for "<<sum<<" chessmen."<<endl;
    }
}
//hdu1281
