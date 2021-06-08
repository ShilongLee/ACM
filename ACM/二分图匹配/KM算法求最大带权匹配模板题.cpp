//#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;
const int N=305;
const int INF=0x3f3f3f3f;
int mapp[N][N],numl[N],numr[N],master[N],slack[N],n;
bool visl[N];
bool visr[N];
bool match(int x)
{
    visl[x]=true;
    for(int y=1; y<=n; ++y)
    {
        if(visr[y])
            continue;
        int k=numl[x]+numr[y]-mapp[x][y];
        if(k==0)
        {
            visr[y]=true;
            if(!master[y]||match(master[y]))
            {
                master[y]=x;
                return true;
            }
        }
        else
            slack[y]=min(slack[y],k);
    }
    return false;
}
int KM()
{
    for(int i=1; i<=n; ++i)
    {
        fill(slack,slack+n+1,INF);
        while(1)
        {
            memset(visl,false,sizeof(visl));
            memset(visr,false,sizeof(visr));
            if(match(i))
                break;
            int d=INF;
            for(int j=1; j<=n; ++j)
                if(!visr[j])
                    d=min(d,slack[j]);
            for(int j=1; j<=n; ++j)
            {
                if(visl[j])
                    numl[j]-=d;
                if(visr[j])
                    numr[j]+=d;
                else
                    slack[j]-=d;
            }
        }
    }
    int res=0;
    for(int i=1; i<=n; ++i)
        res+=mapp[master[i]][i];
    return res;
}
int main()
{
//    ios::sync_with_stdio(false);
//    cin.tie(0);
    while(~scanf("%d",&n))
    {
        for(int i=1; i<=n; ++i)
            for(int j=1; j<=n; ++j)
                scanf("%d",&mapp[i][j]);
                //cin>>mapp[i][j];
        memset(master,0,sizeof(master));
        memset(numr,0,sizeof(numr));
        memset(numl,0,sizeof(numl));
        for(int i=1; i<=n; ++i)
            for(int j=1; j<=n; ++j)
                numl[i]=max(numl[i],mapp[i][j]);
        int ans=KM();
        printf("%d\n",ans);
        //cout<<ans<<endl;
    }
    return 0;
}
//hdu2255
