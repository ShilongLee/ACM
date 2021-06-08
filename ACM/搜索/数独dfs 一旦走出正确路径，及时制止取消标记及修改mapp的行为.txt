#include<cstdio>
#include<algorithm>
#include<math.h>
#include<cstring>
#include<iostream>
#include<queue>
using namespace std;
int mp[11][11];
int l[11][11];
int c[11][11];
int sq[11][11];
int dfs(int x,int y)
{
    int flag=0;
    if(x==9) return 1;
    if(mp[x][y])
    {
        if(y==8) flag=dfs(x+1,0);
        else flag=dfs(x,y+1);
        return flag;
    }
    else
    {
        int z=3*(x/3)+(y/3);
        for(int i=1; i<=9; i++)
        {
            if(!l[x][i]&&!c[y][i]&&!sq[z][i])
            {
                l[x][i]=1;
                c[y][i]=1;
                sq[z][i]=1;
                mp[x][y]=i;
                if(y==8) flag=dfs(x+1,0);
                else flag=dfs(x,y+1);
                if(flag) return 1;
                else
                {
                    l[x][i]=0;
                    c[y][i]=0;
                    sq[z][i]=0;
                    mp[x][y]=0;
                }
            }
        }
        return 0;
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        memset(l,0,sizeof(l));
        memset(c,0,sizeof(c));
        memset(sq,0,sizeof(sq));
        for(int i=0; i<=8; i++)
        {
            for(int j=0; j<=8; j++)
            {
                scanf("%01d",&mp[i][j]);
                l[i][mp[i][j]]=1;
                c[j][mp[i][j]]=1;
                sq[3*(i/3)+(j/3)][mp[i][j]]=1;
            }
        }
        dfs(0,0);
        for(int i=0; i<=8; i++)
        {
            for(int j=0; j<=8; j++)
            {
                printf("%d",mp[i][j]);
            }
            printf("\n");
        }
    }
}
//POJ 2676