#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
const int N=105;
int n,master[N],sum,cnt;
bool mapp[N][N],vis[N];
int a[N],b[N];
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
int main()
{
    while(cin>>n)
    {
        sum=cnt=0;
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        memset(master,0,sizeof(master));
        for(int i=1; i<=n; ++i)
            for(int j=1; j<=n; ++j)
                cin>>mapp[i][j];
        for(int i=1; i<=n; ++i)
        {
            memset(vis,false,sizeof(vis));
            if(match(i))
                sum++;
        }
        if(sum!=n)
        {
            cout<<-1<<endl;
            continue;
        }
        for(int i=1; i<=n; ++i)
        {
            if(i==master[i])
                continue;
            for(int j=i+1; j<=n; ++j)
                if(master[j]==i)
                {
                    a[++cnt]=i,b[cnt]=j;
                    swap(master[i],master[j]);
                    break;
                }
        }
        cout<<cnt<<endl;
        for(int i=1;i<=cnt;++i)
            cout<<"C "<<a[i]<<" "<<b[i]<<""<<endl;
    }
    return 0;
}
//hdu2819
