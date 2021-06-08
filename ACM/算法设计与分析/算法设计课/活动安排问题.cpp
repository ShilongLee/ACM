#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;
struct act
{
    int s,e;
}a[1005];
bool cmp(act a,act b)
{
    return a.e<b.e;
}
int main()
{
    memset(a,0,sizeof(a));
    int n,sum=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&a[i].s,&a[i].e);
        sort(a+1,a+n+1,cmp);
        int e=0;
        for(int i=1;i<=n;i++)
        {
            if(a[i].s>e)
            {
                printf("%d ",i);
                sum++;
                e=a[i].e;
            }
        }
        printf("\n%d\n",sum);
}
