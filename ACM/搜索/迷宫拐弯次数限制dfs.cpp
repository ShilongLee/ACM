#include<stdio.h>
#include<string.h>
#define Max 999999
char s[105][105];
int turn[105][105];
int dir1[4][2]={1,0,0,1,-1,0,0,-1};
int k,x1,y1,x2,y2,ok;
int m,n;
void dfs(int x,int y,int dir)
{
    int xx,yy;
    if(x==x2&&y==y2&&turn[x][y]<=k)
    {
        ok=1;
        return ;
    }
    if(turn[x][y]>k)
        return ;
    if(x!=x2&&y!=y2&&turn[x][y]==k)
        return ;
    for(int i=0; i<4; i++)
    {
        xx=x+dir1[i][0];
        yy=y+dir1[i][1];

        if(xx<=0||yy<=0||xx>m||yy>n||s[xx][yy]=='*')
            continue;
        if(turn[xx][yy]<turn[x][y])
            continue;
        if(dir!=-1&&i!=dir&&turn[xx][yy]<turn[x][y]+1)
            continue;
        if(dir!=-1&&i!=dir)
            turn[xx][yy]=turn[x][y]+1;
        else turn[xx][yy]=turn[x][y];
        s[xx][yy]='*';
        dfs(xx,yy,i);
        s[xx][yy]='.';
        if(ok)
            return ;
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&m,&n);
        for(int i=1;i<=m;i++)
			for(int j=1;j<=n;j++)
				scanf(" %c",&s[i][j]);
        scanf("%d%d%d%d%d",&k,&y1,&x1,&y2,&x2);
        memset(turn,Max,sizeof(turn));
        ok=0;
        turn[x1][y1]=0;
        dfs(x1,y1,-1);
        if(ok)
            printf("yes\n");
        else printf("no\n");
    }
}

//HDU 1728