#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
const int N=205;
const int M=30005;
const int inf=0x3f3f3f3f;
int n,m,v[M],w[M],first[M],ext[M],num,numl[N],numr[N],master[N],slack[N];
bool visl[N],visr[N];
void add(int x,int y,int z)
{
    v[++num]=y;
    w[num]=z;
    ext[num]=first[x];
    first[x]=num;
}
bool match(int x)
{
    visl[x]=true;
    for(int i=first[x]; ~i; i=ext[i])
    {
        int y=v[i];
        if(visr[y])
            continue;
        int k=numl[x]+numr[y]-w[i];
        if(k==0)
        {
            visr[y]=true;
            if(!master[y]||match(master[y]))
            {
                master[y]=x;
                return true;
            }
        }
        else slack[y]=min(slack[y],k);
    }
    return false;
}
int KM()
{
    memset(numl,0,sizeof(numl));
    memset(numr,0,sizeof(numr));
    memset(master,0,sizeof(master));
    for(int i=1; i<=n; ++i)
        for(int j=first[i]; ~j; j=ext[j])
            numl[i]=max(numl[i],w[j]);
    for(int i=1; i<=n; ++i)
    {
        fill(slack,slack+n+1,inf);
        while(1)
        {
            memset(visl,false,sizeof(visl));
            memset(visr,false,sizeof(visr));
            if(match(i))
                break;
            int d=inf;
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
        res+=numl[i];
    for(int i=1; i<=n; ++i)
        res+=numr[i];
    return -res;
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
        num=0;
        cin>>n>>m;
        for(int i=1; i<=m; ++i)
        {
            int x,y,z;
            cin>>x>>y>>z;
            add(x,y,-z);
        }
        int ans=KM();
        cout<<ans<<endl;
    }
    return 0;
}
//hdu3488
