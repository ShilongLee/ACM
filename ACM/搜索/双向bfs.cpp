#include<stdio.h>
#include<algorithm>
#include<queue>
#include<string.h>
#include<iostream>
using namespace std;
const int maxn=805;
char mapp[maxn][maxn];
int vis[maxn][maxn];
int n,m,step,ans;
int dir[4][2]= {0,1,1,0,0,-1,-1,0};
struct node
{
    int x,y;
} M,G,Z[2];
bool ok(int x,int y)
{
    if(x<0||x>=n||y<0||y>=m||mapp[x][y]=='X')
        return false;
    if(min(abs(x-Z[0].x)+abs(y-Z[0].y),abs(x-Z[1].x)+abs(y-Z[1].y))<=step*2)
        return false;
    return true;
}
void bfs()
{
    queue<node>qm;
    queue<node>qg;
    qm.push(M);
    qg.push(G);
    while(!qm.empty()&&!qg.empty())
    {
        step++;
        for(int k=0; k<3; k++)
            for(int i=0,len=qm.size(); i<len; i++)
            {
                node m=qm.front();
                qm.pop();
                if(!ok(m.x,m.y))
                    continue;
                for(int j=0; j<4; j++)
                {
                    node ext;
                    ext.x=m.x+dir[j][0];
                    ext.y=m.y+dir[j][1];
                    if(!ok(ext.x,ext.y)||vis[ext.x][ext.y]==3)
                        continue;
                    if(vis[ext.x][ext.y]==1)
                    {
                        ans=step;
                        return;
                    }
                    vis[ext.x][ext.y]=3;
                    qm.push(ext);
                }
            }
        for(int i=0,len=qg.size(); i<len; i++)
        {
            node g=qg.front();
            qg.pop();
            if(!ok(g.x,g.y))
                continue;
            for(int j=0; j<4; j++)
            {
                node ext;
                ext.x=g.x+dir[j][0];
                ext.y=g.y+dir[j][1];
                if(!ok(ext.x,ext.y)||vis[ext.x][ext.y]==1)
                    continue;
                if(vis[ext.x][ext.y]==3)
                {
                    ans=step;
                    return;
                }
                vis[ext.x][ext.y]=1;
                qg.push(ext);
            }
        }
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        ans=0;
        step=0;
        memset(vis,0,sizeof(vis));
        scanf("%d%d",&n,&m);
        for(int i=0; i<n; i++)
            scanf("%s",mapp[i]);
        int z=0;
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
            {
                if(mapp[i][j]=='M')
                {
                    M.x=i;
                    M.y=j;
                    vis[i][j]=3;
                }
                else if(mapp[i][j]=='G')
                {
                    G.x=i;
                    G.y=j;
                    vis[i][j]=1;
                }
                else if(mapp[i][j]=='Z')
                {
                    Z[z].x=i;
                    Z[z].y=j;
                    z++;
                }
            }
        bfs();
        if(ans)
            printf("%d\n",ans);
        else
            printf("-1\n");
    }
}

//hdu 3085