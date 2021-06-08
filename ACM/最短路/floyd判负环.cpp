#include<iostream>
#include<string.h>
using namespace std;
const int N=505;
const int inf=0x3f3f3f3f;
int n,m,w;
int mapp[N][N];
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        cin>>n>>m>>w;
        memset(mapp,inf,sizeof(mapp));
        for(int i=1; i<=m; ++i)
        {
            int x,y,z;
            cin>>x>>y>>z;
            mapp[x][y]=mapp[y][x]=min(mapp[x][y],z);
        }
        for(int i=1; i<=w; ++i)
        {
            int x,y,z;
            cin>>x>>y>>z;
            mapp[x][y]=min(mapp[x][y],-z);
        }
        int flag=0;
        for(int k=1; k<=n; ++k)
            for(int i=1; i<=n; ++i)
            {
                if(mapp[i][k]==inf)
                    continue;
                for(int j=1; j<=n; ++j)
                    if(mapp[i][j]>mapp[i][k]+mapp[k][j])
                    mapp[i][j]=mapp[i][k]+mapp[k][j];
                    //mapp[i][j]=min(mapp[i][j],mapp[i][k]+mapp[k][j]);
            }
            for(int i=1; i<=N; ++i)
                    if(mapp[i][i]<0)
                        flag=1;
        if(flag)
            cout<<"YES"<<endl;
        else
            cout<<"NO"<<endl;
    }
}
//floyd判负环
//poj3259