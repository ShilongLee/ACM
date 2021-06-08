#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
int a[505];
int dp[505];
void dpp(int n)
{
    for(int i=0;i<n;i++)
        dp[i]=max(a[i],dp[i-1]+a[i]);
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    dp[0]=0;
    dpp(n);
    printf("%d\n",dp[n-1]);
}
