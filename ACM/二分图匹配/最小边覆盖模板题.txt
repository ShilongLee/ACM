#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
const int N=405;
int mapp[N][N];
int n,m,cnt,v[N*N],first[N*N],ext[N*N],num,master[N<<1],vis[N<<1],sum;
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
        cnt=num=sum=0;
        memset(master,0,sizeof(master));
        memset(mapp,0,sizeof(mapp));
        memset(first,-1,sizeof(first));
        cin>>n>>m;
        for(int i=1; i<=n; ++i)
            for(int j=1; j<=m; ++j)
            {
                char c;
                cin>>c;
                if(c=='*')
                    mapp[i][j]=++cnt;
            }
        for(int i=1; i<=n; ++i)
            for(int j=1; j<=m; ++j)
                if(mapp[i][j])
                {
                    if(i+1<=n&&mapp[i+1][j])
                        add(mapp[i][j],mapp[i+1][j]),add(mapp[i+1][j],mapp[i][j]);
                    if(j+1<=m&&mapp[i][j+1])
                        add(mapp[i][j],mapp[i][j+1]),add(mapp[i][j+1],mapp[i][j]);
                }
        for(int i=1;i<=cnt;++i)
        {
            memset(vis,0,sizeof(vis));
            if(match(i)) sum++;
        }
        cout<<cnt-sum/2<<endl;
    }
    return 0;
}
//poj3020
