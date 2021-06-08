#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;
const int N=50005;
int a[N];
int max1[N][50];
int min1[N][50];
int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=1; i<=n; ++i)
        scanf("%d",&a[i]);
    for(int i=1; i<=n; ++i)
    {
        max1[i][0]=a[i];
        min1[i][0]=a[i];
    }
    for(int j=1; (1<<j)<=n; ++j)
        for(int i=1; i+(1<<j)-1<=n; ++i)
        {
            max1[i][j]=max(max1[i][j-1],max1[i+(1<<(j-1))][j-1]);
            min1[i][j]=min(min1[i][j-1],min1[i+(1<<(j-1))][j-1]);
        }
    int l,r;
    while(q--)
    {
        scanf("%d%d",&l,&r);
        int k=0;
        while(1<<(k+1)<=r-l+1)
            ++k;
        int ans1=max(max1[l][k],max1[r-(1<<k)+1][k]);
        int ans2=min(min1[l][k],min1[r-(1<<k)+1][k]);
       printf("%d\n",ans1-ans2);
    }
}
//poj3264