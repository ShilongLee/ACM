#include<iostream>
#include<algorithm>
#include<string.h>
#include<queue>
using namespace std;
const int N=605;
const int inf=0x3f3f3f3f;
int n,cnt;
int mapp[N][N],v[N*N<<1],first[N*N<<1],ext[N*N<<1],num,usedx[N*N<<1],usedy[N*N<<1],dx[N*N<<1],dy[N*N<<1],vis[N*N<<1],sum;
void add(int x,int y)
{
    v[++num]=y;
    ext[num]=first[x];
    first[x]=num;
}
bool bfs()
{
    queue<int>q;
    memset(dx,-1,sizeof(dx));
    memset(dy,-1,sizeof(dy));
    for(int i=1; i<=cnt; ++i)
        if(!usedx[i])
        {
            dx[i]=0;
            q.push(i);
        }
    int depth=inf;
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
int main()
{
    int t,cas=0;
    cin>>t;
    while(t--)
    {
        memset(mapp,0,sizeof(mapp));
        memset(usedx,0,sizeof(usedx));
        memset(usedy,0,sizeof(usedy));
        memset(first,-1,sizeof(first));
        cnt=num=sum=0;
        cin>>n;
        for(int i=1; i<=n; ++i)
            for(int j=1; j<=n; ++j)
            {
                char c;
                cin>>c;
                if(c=='#')
                    mapp[i][j]=++cnt;
            }
        for(int i=1; i<=n; ++i)
            for(int j=1; j<=n; ++j)
            {
                if(mapp[i][j])
                {
                    if(i-1>=1&&mapp[i-1][j])
                    {
                        add(mapp[i][j],mapp[i-1][j]);
                        add(mapp[i-1][j],mapp[i][j]);
                    }
                    if(j-1>=1&&mapp[i][j-1])
                    {
                        add(mapp[i][j],mapp[i][j-1]);
                        add(mapp[i][j-1],mapp[i][j]);
                    }
                }
            }
        while(bfs())
        {
            memset(vis,0,sizeof(vis));
            for(int i=1; i<=cnt; ++i)
                if(!usedx[i]&&match(i))
                    sum++;
        }
        cout<<"Case "<<++cas<<": "<<sum/2<<""<<endl;
    }
    return 0;
}
//hdu 4185
