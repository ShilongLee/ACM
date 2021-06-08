#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<queue>
#include<stack>
#include<string.h>
using namespace std;
int m,n,ok;
int maze[5005][5005];
int dir[8][2]= {0,1,1,0,-1,0,0,-1,1,1,-1,1,1,-1,-1,-1};
struct node
{
    int x,y;
} now,ext,via[5005][5005];
stack<node>road;
void cprintf(int a,int b)
{
    if(via[a][b].x!=-1&&via[a][b].y!=-1)
    {
        node s;
        s.x=via[a][b].x;
        s.y=via[a][b].y;
        road.push(s);
        cprintf(via[a][b].x,via[a][b].y);
    }
}
void bfs(node a)
{
    queue<node>q;
    q.push(a);
    via[a.x][a.y].x=-1;
    via[a.x][a.y].y=-1;
    while(!q.empty())
    {
        node cur;
        cur=q.front();
        q.pop();
        if(cur.x==m&&cur.y==n)
        {
            ok=1;
            node k;
            k.x=m;
            k.y=n;
            road.push(k);
            cprintf(m,n);
        }
        for(int i=0; i<8; i++)
        {
            ext.x=cur.x+dir[i][0];
            ext.y=cur.y+dir[i][1];
            if(maze[ext.x][ext.y]==0&&ext.x>=1&&ext.x<=m&&ext.y>=1&&ext.y<=n)
            {
                q.push(ext);
                maze[ext.x][ext.y]=1;
                via[ext.x][ext.y].x=cur.x;
                via[ext.x][ext.y].y=cur.y;
            }
        }
    }
}
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1; i<=m; i++)
        for(int j=1; j<=n; j++)
            scanf("%d",&maze[i][j]);
    maze[1][1]=1;
    now.x=1;
    now.y=1;
    bfs(now);
    printf("%d\n",ok);
    while(!road.empty())
    {
        printf("%d %d\n",road.top().x,road.top().y);
        road.pop();
    }
}