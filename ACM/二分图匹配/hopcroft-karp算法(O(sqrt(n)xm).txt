#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<queue>
using namespace std;
const int N=3005;
const int M=3005;
const int K=N*M;
const int inf=0x3f3f3f3f;
struct guest
{
    int x,y;
    int v;
} g[N];
struct umbrella
{
    int x,y;
} u[M];
int dis(guest a,umbrella b)
{
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
int t,n,m,v[K],first[K],ext[K],num,sum,dx[N<<1],dy[M<<1],usedx[N<<1],usedy[M<<1];
bool vis[N<<1];
void add(int x,int y)
{
    v[++num]=y;
    ext[num]=first[x];
    first[x]=num;
}
bool match(int x)
{
    for(int i=first[x]; ~i; i=ext[i])
    {
        int y=v[i];
        if(!vis[y]&&dy[y]==dx[x]+1)
        {
            vis[y]=true;
            if(!usedy[y]||match(usedy[y]))
            {
                usedy[y]=x;
                usedx[x]=y;
                return true;
            }
        }
    }
    return false;
}
bool bfs()
{
    queue<int>q;
    int depth=inf;
    memset(dx,-1,sizeof(dx));
    memset(dy,-1,sizeof(dy));
    for(int i=1; i<=n; ++i)
        if(!usedx[i])
        {
            dx[i]=0;
            q.push(i);
        }
    while(!q.empty())
    {
        int f=q.front();
        q.pop();
        if(depth<dx[f])
            break;
        for(int i=first[f]; ~i; i=ext[i])
        {
            int p=v[i];
            if(dy[p]==-1)
            {
                dy[p]=dx[f]+1;
                if(!usedy[p])
                    depth=dy[p];
                else
                {
                    dx[usedy[p]]=dy[p]+1;
                    q.push(usedy[p]);
                }
            }
        }
    }
    if(depth==inf)
        return false;
    return true;
}
int main()
{
    int kase;
    scanf("%d",&kase);
    for(int kas=1; kas<=kase; kas++)
    {
        num=sum=0;
        memset(usedx,0,sizeof(usedx));
        memset(usedy,0,sizeof(usedy));
        memset(first,-1,sizeof(first));
        scanf("%d",&t);
        scanf("%d",&n);
        for(int i=1; i<=n; ++i)
            scanf("%d%d%d",&g[i].x,&g[i].y,&g[i].v);
        scanf("%d",&m);
        for(int i=1; i<=m; ++i)
            scanf("%d%d",&u[i].x,&u[i].y);
        for(int i=1; i<=n; ++i)
            for(int j=1; j<=m; ++j)
                if(dis(g[i],u[j])<=t*t*g[i].v*g[i].v)
                    add(i,j+n);
        memset(dx,-1,sizeof(dx));
        memset(dy,-1,sizeof(dy));
        while(bfs())
        {
            memset(vis,0,sizeof(vis));
            for(int i=1; i<=n; ++i)
                if(!usedx[i]&&match(i))
                    sum++;
        }
        printf("Scenario #%d:\n",kas);
        printf("%d\n\n",sum);
    }
    return 0;
}
//hdu2389
