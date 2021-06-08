#include<stdio.h>
#include<math.h>
#include<string.h>
#include<algorithm>
using namespace std;
char mapp[8][8];
int vis[8][8];
int n,m,t,sx,sy,ex,ey,ok;
int dir[4][2]= {0,1,1,0,-1,0,0,-1};
void dfs(int x,int y,int step)
{
    if(step>t) return ;
    if(x==ex&&y==ey&&step==t)
    {
        ok=1;
        return ;
    }
    if(ok)
        return;
    for(int i=0; i<4; i++)
    {
        int xx=x+dir[i][0];
        int yy=y+dir[i][1];
        if(xx<0||xx>=n||yy<0||yy>=m||vis[xx][yy]||mapp[xx][yy]=='X')
            continue;
        vis[xx][yy]=1;
        dfs(xx,yy,step+1);
        vis[xx][yy]=0;
    }
}
int main()
{
    while(~scanf("%d%d%d",&n,&m,&t)&&n&&m&&t)
    {
        ok=0;
        memset(vis,0,sizeof(vis));
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
            {
                scanf(" %c",&mapp[i][j]);
                if(mapp[i][j]=='S')
                    sx=i,sy=j;
                if(mapp[i][j]=='D')
                    ex=i,ey=j,mapp[i][j]='.';
            }
        vis[sx][sy]=1;
        if(abs(ex-sx)+abs(ey-sy)-t>0||(abs(ex-sx)+abs(ey-sy)-t)%2)
        {
            printf("NO\n");
            continue;
        }
        dfs(sx,sy,0);
        if(ok)
            printf("YES\n");
        else
            printf("NO\n");
    }
}
//只能用dfs，bfs求的只是最短路，本题要求步数正好。
//并且bfs没有回溯，走过的点不会再次走，所以一但到达终点，但是此时还没达到步数就不可能到达终点，所以bfs不行。
//XXS..
//XX..X
//X...X
//X.D.X
 //HDU 1010 