#include<string.h>
#include<algorithm>
#include<iostream>
using namespace std;
const int N=1005;
int n,cnt,sum;
int mapp[N][N],vis[N],master[N];//master是和右边匹配的点 a和b匹配 master[b]=a
int g[N][N];//关系矩阵图


bool match(int x)
{
    for(int y=1; y<=cnt; ++y)
    {
        if(!vis[y]&&g[x][y])
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
    int t;
    cin>>t;
    for(int k=1; k<=t; ++k)
    {
        cnt=sum=0;
        memset(mapp,0,sizeof(mapp));
        memset(master,0,sizeof(master));
        memset(g,0,sizeof(g));

        cin>>n;

        for(int i=1; i<=n; ++i)
            for(int j=1; j<=n; ++j)
            {
                char c;
                cin>>c;
                if(c=='#')
                    mapp[i][j]=++cnt;
            }


        for(int i=1; i<=n; ++i)
            for(int j=1; j<=n; ++j)
            {
                if(mapp[i][j])
                {
                    if(i-1>=1&&mapp[i-1][j])
                        g[mapp[i][j]][mapp[i-1][j]]=g[mapp[i-1][j]][mapp[i][j]]=1;
                    if(j-1>=1&&mapp[i][j-1])
                        g[mapp[i][j]][mapp[i][j-1]]=g[mapp[i][j-1]][mapp[i][j]]=1;
                }
            }


        for(int i=1; i<=cnt; ++i)
        {
            memset(vis,0,sizeof(vis));
            if(match(i))
                sum++;
        }


        cout<<"Case "<<k<<": "<<sum/2<<""<<endl;
    }
    return 0;
}
//hdu4185
//左右有关系指左右匹配后，匹配过的两个点都不能再进行匹配