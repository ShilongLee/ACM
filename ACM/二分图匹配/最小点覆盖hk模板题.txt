#include<stdio.h>
#include<string.h>
#include<queue>
#include<algorithm>
using namespace std;
const int N=1505;
const int inf=0x3f3f3f3f;
int v[N*N<<1],first[N*N<<1],ext[N*N<<1],num,n,dx[N],dy[N],usedx[N],usedy[N],vis[N],sum;
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
    for(int i=1;i<=n;++i)
        if(!usedx[i])
    {
        dx[i]=0;
        q.push(i);
    }
    while(!q.empty())
    {
        int f=q.front();
        q.pop();
        if(depth<dx[f]) break;
        for(int i=first[f];~i;i=ext[i])
        {
            int y=v[i];
            if(dy[y]==-1)
            {
                dy[y]=dx[f]+1;
                if(!usedy[y])
                    depth=dy[y];
                else
                {
                    dx[usedy[y]]=dy[y]+1;
                    q.push(usedy[y]);
                }
            }
        }
    }
    if(depth==inf) return false;
    return true;
}
int main()
{
    while(~scanf("%d",&n))
    {
        memset(usedx,0,sizeof(usedx));
        memset(vis,0,sizeof(vis));
        memset(usedy,0,sizeof(usedy));
        memset(first,-1,sizeof(first));
        num=sum=0;
        for(int i=1;i<=n;++i)
        {
            int x,k,y;
            scanf("%d:(%d)",&x,&k);
            x++;
            while(k--)
            {
                scanf("%d",&y);
                y++;
                add(x,y);
                add(y,x);
            }
        }
        while(bfs())
        {
            memset(vis,0,sizeof(vis));
            for(int i=1;i<=n;++i)
            if(!usedx[i]&&match(i)) sum++;
        }
        printf("%d\n",sum>>1);
    }
}
//hdu1054
