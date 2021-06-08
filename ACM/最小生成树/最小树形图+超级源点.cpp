#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int N=1005;
const int M=20005;
const int inf=0x3f3f3f3f;
int n,m,rt[N],vis[N],id[N],in[N],pos;
struct Edge
{
    int x,y;
    int w;
} edge[M];
int zhuLiu(int root,int n,int m)
{
    int ans=0;
    while(true)
    {
        for(int i=1; i<=n; ++i)
            in[i]=inf;
        for(int i=1; i<=m; ++i)
        {
            int x=edge[i].x;
            int y=edge[i].y;
            if(edge[i].w<in[y]&&x!=y)
            {
                in[y]=edge[i].w;
                rt[y]=x;
                if(x==root)
                    pos=i;
            }
        }
        for(int i=1; i<=n; ++i)
            if(i!=root&&in[i]==inf)
                return -1;
        int cnt=0;
        in[root]=0;
        memset(vis,-1,sizeof(vis));
        memset(id,-1,sizeof(id));
        for(int i=1; i<=n; ++i)
        {
            ans+=in[i];
            int y=i;
            while(vis[y]!=i&&id[y]==-1&&y!=root)
            {
                vis[y]=i;
                y=rt[y];
            }
            if(y!=root&&id[y]==-1)
            {
                id[y]=++cnt;
                for(int x=rt[y]; x!=y; x=rt[x])
                    id[x]=cnt;
            }
        }
        if(cnt==0)
            break;
        for(int i=1; i<=n; ++i)
            if(id[i]==-1)
                id[i]=++cnt;
        for(int i=1; i<=m; ++i)
        {
            int x=edge[i].x;
            int y=edge[i].y;
            edge[i].x=id[x];
            edge[i].y=id[y];
            if(id[x]!=id[y])
                edge[i].w-=in[y];
        }
        n=cnt;
        root=id[root];
    }
    return ans;
}
int main()
{
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        int sum=1;
        for(int i=1; i<=m; ++i)
        {
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            x++,y++;
            if(x!=y)
                sum+=z;
            if(x==y)
                z=inf;
            edge[i].x=x;
            edge[i].y=y;
            edge[i].w=z;
        }
        for(int i=1; i<=n; ++i)
        {
            edge[m+i].x=n+1;
            edge[m+i].y=i;
            edge[m+i].w=sum;
        }
        int ans=zhuLiu(n+1,n+1,m+n);
        if(ans-sum>=sum||ans==-1) printf("impossible\n");
        else printf("%d %d\n",ans-sum,pos-m-1);
        printf("\n");
    }
}
//hdu2121
