#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;
int mapp[15][15];
int vis[15];
int sum=0;
int n,k;
char c;
void dfs(int step,int col)
{
    if(col>n)
        return ;
    if(step==k)
    {
        sum++;
        return ;
    }
    for(int i=0; i<n; i++)
    {
        if(mapp[col][i]==0&&vis[i]==0)
        {
            vis[i]=1;
            mapp[col][i]=1;
            dfs(step+1,col+1);
            vis[i]=0;
            mapp[col][i]=0;
        }
    }
    dfs(step,col+1);
}
int main()
{
    while(~scanf("%d%d",&n,&k)&&n!=-1&&k!=-1)
    {
        memset(vis,0,sizeof(vis));
        sum=0;
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
            {
                scanf(" %c",&c);
                if(c=='#')
                    mapp[i][j]=0;
                else if (c=='.')
                    mapp[i][j]=1;
            }
        dfs(0,0);
        printf("%d\n",sum);
    }
}


//POJ1321