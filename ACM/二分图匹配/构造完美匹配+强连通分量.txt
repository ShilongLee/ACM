#include<stdio.h>
#include<algorithm>
#include<stack>
#include<string.h>
using namespace std;
const int N=2505;
const int M=2505;
int n,m,v[N*M],first[N*M],fin[N*2],ext[N*M],num,p[M],sum,ok[N*2],dfn[N*2],low[N*2],cnt,tot,col[N*2],ans[N*2],like[N*2];
bool vis[M];
stack<int>s;
void init()
{
    num=sum=tot=cnt=0;
    memset(first,-1,sizeof(first));
    memset(like,0,sizeof(like));
    //memset(fin,0,sizeof(fin));
    memset(ans,0,sizeof(ans));
    //memset(ok,0,sizeof(ok));
    memset(vis,false,sizeof(vis));
    memset(p,0,sizeof(p));
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(col,0,sizeof(col));
}
void add(int x,int y)
{
    v[++num]=y;
    ext[num]=first[x];
    first[x]=num;
}
bool hungary(int x)
{
    for(int i=first[x]; ~i; i=ext[i])
    {
        int y=v[i];
        if(!vis[y])
        {
            vis[y]=true;
            if(!p[y]||hungary(p[y]))
            {
                p[y]=x;
                return true;
            }
        }
    }
    return false;
}
void tarjan(int st)
{
    dfn[st]=low[st]=++cnt;
    vis[st]=true;
    s.push(st);
    for(int i=first[st]; ~i; i=ext[i])
    {
        int p=v[i];
        if(!dfn[p])
        {
            tarjan(p);
            low[st]=min(low[st],low[p]);
        }
        else if(vis[p])
            low[st]=min(low[st],dfn[p]);
    }
    if(dfn[st]==low[st])
    {
        ++tot;
        int k;
        do
        {
            k=s.top();
            vis[k]=false;
            col[k]=tot;
            s.pop();
        }
        while(k!=st);
    }
}
int main()
{
    int t,cas=0;
    scanf("%d",&t);
    while(t--)
    {
        init();
        printf("Case #%d:\n",++cas);
        scanf("%d%d",&n,&m);
        for(int i=1; i<=n; ++i)
        {
            int k,y;
            scanf("%d",&k);
            while(k--)
            {
                scanf("%d",&y);
                add(i,y+n);
            }
        }
        for(int i=1; i<=n; ++i)
        {
            memset(vis,false,sizeof(vis));
            if(hungary(i))
                sum++;
        }
        for(int i=n+1; i<=n+m; ++i)
            like[p[i]]=i;
        int all=n+m;
        for(int i=1; i<=n; ++i)
        {
            if(!like[i])
            {
                like[i]=++all;
                p[all]=i;
                for(int j=1; j<=n; ++j)
                    add(j,all);
            }
        }
        for(int i=n+1; i<=m+n; ++i)
        {
            if(!p[i])
            {
                p[i]=++all;
                like[all]=i;
                for(int j=n+1; j<=n+m; ++j)
                    add(all,j);
            }
        }
        for(int i=1;i<=all;++i)
            if(like[i]) add(like[i],i);
        for(int i=1; i<=n; ++i)
            if(!dfn[i])
                tarjan(i);
        for(int i=1; i<=n; ++i)
        {
            int cnt=0;
            for(int j=first[i]; ~j; j=ext[j])
            {
                int p=v[j];
                if(col[i]==col[p]&&p<=n+m&&p>=n+1)
                    ans[++cnt]=p;
            }
            sort(ans+1,ans+1+cnt);
            printf("%d",cnt);
            for(int i=1; i<=cnt; ++i)
                printf(" %d",ans[i]-n);
            printf("\n");
        }
    }
    return 0;
}
//hdu4685
