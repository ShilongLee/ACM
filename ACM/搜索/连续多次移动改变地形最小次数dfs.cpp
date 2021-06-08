#include<stdio.h>
#include<string.h>
int m,n,mapp[105][105],sx,sy,ex,ey,min1=999999;
int d[4][2]= {1,0,-1,0,0,1,0,-1};
void dfs(int x,int y,int step)
{
    if(step>10)
        return ;
    if(step<=10&&x==ex&&y==ey)
    {
        if(step<min1)
            min1=step;
        return ;
    }
    for(int i=0; i<4; i++)
    {
        int xx=0,yy=0;
        for(int j=1; j<25; j++)
        {
            xx=x+j*d[i][0];
            yy=y+j*d[i][1];
            if(j==1&&mapp[xx][yy]==1)
                break;
            else if(mapp[xx][yy]==1)
            {
                mapp[xx][yy]=0;
                xx=xx-d[i][0];
                yy=yy-d[i][1];
                dfs(xx,yy,step+1);
                 xx=xx+d[i][0];
                yy=yy+d[i][1];
                mapp[xx][yy]=1;
                break;
            }
            else if(mapp[xx][yy]==-1)
                break;
            else if(mapp[xx][yy]==3)
            {
                dfs(xx,yy,step+1);
                break;
            }
        }
    }
}
int main()
{
    while(~scanf("%d%d",&m,&n)&&m&&n)
    {
        min1=999999;
        memset(mapp,-1,sizeof(mapp));
        for (int i=1; i<=n; i++)
            for (int j=1; j<=m; j++)
            {
                scanf("%d",&mapp[i][j]);
                if(mapp[i][j]==2)
                {
                    sx=i,sy=j;
                    mapp[i][j]=0;
                }
                else if(mapp[i][j]==3)
                {
                    ex=i,ey=j;
                }
            }
        dfs(sx,sy,0);
        if(min1==999999)
            printf("-1\n");
        else
            printf("%d\n",min1);
    }
}

//POJ 3009