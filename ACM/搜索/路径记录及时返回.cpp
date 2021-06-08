#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
int mapp[8][8],vis[8][8],Min=99999999,path[8][8];
int check()
{
    int i,j;
    for(i=0; i<4; ++i)
        for(j=0; j<4; ++j)
            if(mapp[i][j]==0)
                return 0;
    return 1;
}
void change(int i,int j)
{
    for(int k=0;k<4;k++)
        mapp[i][k]^=1;
    for(int k=0;k<4;k++)
        mapp[k][j]^=1;
    mapp[i][j]^=1;
}
void dfs(int d,int step)
{
    int x=d/4,y=d%4;
    if(d==16)
    {
        if(check())
        {
            if(Min>step)
            {
                Min=step;
                for(int i=0; i<4; i++)
                    for(int j=0; j<4; j++)
                        path[i][j]=vis[i][j];
            }
        }
        return ;
    }
        dfs(d+1,step);
        change(x,y);
        vis[x][y]=1;
        dfs(d+1,step+1);
        change(x,y);
        vis[x][y]=0;
}
int main()
{
    memset(vis,0,sizeof(0));
    char c;
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
        {
            scanf(" %c",&c);
            if(c=='+')
                mapp[i][j]=0;
            else
                mapp[i][j]=1;
        }
    dfs(0,0);
    cout<<Min<<endl;
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            if(path[i][j])
                printf("%d %d\n",i+1,j+1);
}

//POJ 2965


#include<stdio.h>
#include<string.h>
int p,q,vis[55][55],ok=0,path[55][2];
int dir[8][2]= {-1,-2,1,-2,-2,-1,2,-1,-2,1,2,1,-1,2,1,2};
void dfs(int x,int y,int step)
{

    if(ok)
        return ;
    path[step][0]=x;
    path[step][1]=y;
    if(step==p*q-1)
    {
        ok=1;
        return ;
    }
    for(int i=0; i<8; i++)
    {
        int xx=x+dir[i][0];
        int yy=y+dir[i][1];
        if(xx<0||yy<0||xx>=p||yy>=q||vis[xx][yy])
            continue ;
        vis[xx][yy]=1;
        dfs(xx,yy,step+1);
        vis[xx][yy]=0;
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    for(int op=1; op<=t; op++)
    {
        ok=0;
        memset(vis,0,sizeof(vis));
        scanf("%d%d",&p,&q);
        vis[0][0]=1;
        dfs(0,0,0);
        printf("Scenario #%d:\n",op);
        if(!ok)
            printf("impossible");
        else
        {
            for(int i=0; i<p*q; i++)
                printf("%c%d",path[i][1]+'A',path[i][0]+1);
        }
        printf("\n");
        if(op!=t) printf("\n");
    }
}

//POJ 2488