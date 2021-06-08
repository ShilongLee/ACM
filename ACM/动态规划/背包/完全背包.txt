#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
int c[1005],w[1005],dp[1005];
int main()
{
    int t,n,m,i,j;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(i=1; i<=n; i++)
            scanf("%d",&c[i]);
        for(i=1; i<=n; i++)
            scanf("%d",&w[i]);
        memset(dp,0,sizeof(dp));
        for(i=1; i<=n; i++)
            for(j=w[i]; j<=m; j++)
                dp[j]=max(dp[j],dp[j-w[i]]+c[i]);
                printf("%d\n",dp[m]);
    }
}
