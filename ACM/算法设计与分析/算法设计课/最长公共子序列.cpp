#include<stdio.h>
#include<algorithm>
#include<math.h>
#include<string.h>
using namespace std;
int mapp[1005][1005];
char a[1005];
char b[1005];
void dpmapp(int m,int n)
{
    for(int i=1; i<=m; i++)
    {
        for(int j=1; j<=n; j++)
        {
            if(a[i]==b[j])
                mapp[i][j]=mapp[i-1][j-1]+1;
            else
                mapp[i][j]=max(mapp[i-1][j],mapp[i][j-1]);
        }
    }
}
void LCS(int i,int j)
{
    if(i==0||j==0||!mapp[i][j])
        return ;
    if(mapp[i][j]==mapp[i-1][j-1]+1)
    {
        LCS(i-1,j-1);
        printf("%c",a[i]);
    }
    else
    {
        if(mapp[i-1][j]>=mapp[i][j-1])
            LCS(i-1,j);
        else
            LCS(i,j-1);
    }
}
int main()
{
    while(~scanf("%s%s",a+1,b+1))
    {
        memset(mapp,0,sizeof(mapp));
        int m=strlen(a+1);
        int n=strlen(b+1) ;
        dpmapp(m,n);
        for(int i=1; i<=m; i++)
        {
            for(int j=1; j<=n; j++)
                printf("%d ",mapp[i][j]);
            printf("\n");
        }
        LCS(m,n);
        printf("\n");
    }
}
