#include<iostream>
#include<string.h>
#include<string>
#include<algorithm>
using namespace std;
const int N=105;
const int M=105;
const int P=1505;
int mapp[P][P],vis[P],master[P],sum;
string a[P],b[P];
int n,m,p;
int match(int x)
{
    for(int y=1+p; y<=2*p; ++y)
    {
        if(!vis[y]&&mapp[x][y])
        {
            vis[y]=true;
            if(!master[y]||match(master[y]))
            {
                master[y]=x;
                return mapp[x][y];
            }
        }
    }
    return 0;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    while(cin>>n>>m>>p)
    {
        memset(mapp,0,sizeof(mapp));
        memset(master,0,sizeof(master));
        memset(vis,0,sizeof(vis));
        sum=0;
        for(int i=1; i<=p; ++i)
            cin>>a[i]>>b[i];
        for(int i=1; i<=p; ++i)
            for(int j=1; j<=p; ++j)
            {
                if(a[i]==b[j]||a[j]==b[i])
                    mapp[i][j+p]=mapp[j+p][i]=1;
            }
        for(int i=1; i<=p; ++i)
        {
            memset(vis,0,sizeof(vis));
            if(match(i))
                sum+=1;
        }
        cout<<p-sum/2<<endl;
    }
    return 0;
}
//hdu3829
