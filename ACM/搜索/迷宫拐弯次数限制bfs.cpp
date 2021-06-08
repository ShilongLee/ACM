#include<stdio.h>
#include<queue>
#include<iostream>
#define INF 9999999
using namespace std;
char s[155][155];
int turn[105][105];
struct node
{
    int x;
    int y;
    int turn;
    int dir;
} st,cur,ext;
int x1,m,n,yy,x2,y2,k,ok;
int dir1[4][2]={1,0,0,1,-1,0,0,-1};
void bfs(node st1)
{
    st1.turn=0;
    st1.dir=-1;
    queue<node>q;
    turn[st1.x][st1.y]=0;
    q.push(st1);
    while(!q.empty())
    {
        cur=q.front();
        q.pop();
        if(cur.x==x2&&cur.y==y2&&cur.turn<=k)
        {
            ok=1;
            return ;
        }
        if(cur.turn>k)
            continue ;
        if(cur.x!=x2&&cur.y!=y2&&turn[cur.x][cur.y]==k)
            continue ;
        for(int i=0; i<4; i++)
        {
            ext.x=cur.x+dir1[i][0];
            ext.y=cur.y+dir1[i][1];
            if(ext.x>0&&ext.y>0&&ext.x<=m&&ext.y<=n&&s[ext.x][ext.y]=='.')
            {
                if(cur.dir!=i&&cur.dir!=-1)
                {
                    ext.dir=i;
                    ext.turn=cur.turn+1;
                    if(ext.turn<=turn[ext.x][ext.y])
                    {
                        turn[ext.x][ext.y]=ext.turn;
                        q.push(ext);
                    }
                }
                else
                {
                    ext.dir=i;
                    ext.turn=cur.turn;
                    if(ext.turn<=turn[ext.x][ext.y])
                    {
                        turn[ext.x][ext.y]=ext.turn;
                        q.push(ext);
                    }
                }
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
        ok=0;
        scanf("%d%d",&m,&n);
        for(int i=1; i <=m; i++)
            for(int j=1; j <=n; j++)
                turn[i][j] = INF;
        for(int i=1; i<=m; i++)
            for(int j=1; j<=n; j++)
                scanf(" %c",&s[i][j]);
        scanf("%d%d%d%d%d",&k,&yy,&x1,&y2,&x2);
        st.x=x1;
        st.y=yy;
        bfs(st);
        if(ok)
            printf("yes\n");
        else printf("no\n");
    }
}
//HDU 1728