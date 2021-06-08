#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;
int a[100005];
int b[100005];
int BS(int a,int n)
{
    int l=1,r=n,mid;
    while(l<=r)
    {
        mid=(l+r)/2;
        if(b[mid]<=a) l=mid+1;
        else r=mid-1;
    }
    return l;
}
int LIS(int n)
{
    int pos=1;
    for(int i=0; i<n; i++)
    {
        if(a[i]>b[pos-1])
            b[pos++]=a[i];
            else b[BS(a[i],pos)]=a[i];
    }
    return pos-1;
}
int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        for(int i=0; i<n; i++)
            scanf("%d",&a[i]);
        printf("%d\n",LIS(n));
    }
}
