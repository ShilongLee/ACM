#include<stdio.h>
#include<algorithm>
#include<iostream>
#include<string.h>
using namespace std;
const long long N=1005;
const long long M=N*N;
const long long inf=0x3f3f3f3f;
long long n,X,Y,Z,rt[N],in[N],vis[N],id[N];
struct pos
{
    long long x,y,h;
} home[N];
struct Edge
{
    long long x,y,len;
} edge[M+N];
long long dis(pos a,pos b)
{
    return abs(a.x-b.x)+abs(a.y-b.y)+abs(a.h-b.h);
}
long long zhuliu(long long root,long long n,long long m)
{
    long long ans=0;
    while(true)
    {
        for(long long i=1; i<=n; ++i)
            in[i]=inf;
        for(long long i=1; i<=m; ++i)
        {
            long long x=edge[i].x;
            long long y=edge[i].y;
            if(edge[i].len<in[y]&&x!=y)
            {
                in[y]=edge[i].len;
                rt[y]=x;
            }
        }
        for(long long i=1; i<=n; ++i)
            if(i!=root&&in[i]==inf)
                return -1;
        long long cnt=0;
        in[root]=0;
        memset(vis,-1,sizeof(vis));
        memset(id,-1,sizeof(id));
        for(long long i=1; i<=n; ++i)
        {
            ans+=in[i];
            long long y=i;
            while(vis[y]!=i&&id[y]==-1&&y!=root)
            {
                vis[y]=i;
                y=rt[y];
            }
            if(y!=root&&id[y]==-1)
            {
                id[y]=++cnt;
                for(long long x=rt[y]; x!=y; x=rt[x])
                    id[x]=cnt;
            }
        }
        if(cnt==0)
            break;
        for(long long i=1; i<=n; ++i)
            if(id[i]==-1)
                id[i]=++cnt;
        for(long long i=1; i<=m; ++i)
        {
            long long x=edge[i].x;
            long long y=edge[i].y;
            edge[i].x=id[x];
            edge[i].y=id[y];
            if(id[x]!=id[y])
                edge[i].len-=in[y];
        }
        n=cnt;
        root=id[root];
    }
    return ans;
}
int main()
{

    while(~scanf("%lld%lld%lld%lld",&n,&X,&Y,&Z))
    {
        if(n==0&&X==0&&Y==0&&Z==0)
            break;
        long long num=0;
        for(long long i=1; i<=n; ++i)
            scanf("%lld%lld%lld",&home[i].x,&home[i].y,&home[i].h);
        for(long long i=1; i<=n; ++i)
        {
            long long k,j;
            scanf("%lld",&k);
            while(k--)
            {
                scanf("%lld",&j);
                edge[++num].x=i;
                edge[num].y=j;
                if(home[i].h<home[j].h)
                    edge[num].len=Z;
                else
                    edge[num].len=0;
                edge[num].len+=dis(home[i],home[j])*Y;
                if(i==j)
                    edge[num].len=inf;
            }
        }
        for(long long i=1; i<=n; ++i)
        {
            edge[++num].x=n+1;
            edge[num].y=i;
            edge[num].len=home[i].h*X;
        }
        long long ans=zhuliu(n+1,n+1,num);
        if(ans==-1)
            printf("poor XiaoA\n");
        else
            printf("%lld\n",ans);
    }
    return 0;
}
//hdu4009
