#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;
int a[5005];
int n;
int x;
int f(int x,int l,int r)
{
    if(l>r)
    {
        if(a[l]==x)
            return l;
        else return -1;
    }
    int mid=(l+r)/2;
    if(a[mid]>=x) return f(x,l,mid-1);
    else if(a[mid]<x) return f(x,mid+1,r);
}
int main()
{
    while(~scanf("%d%d",&n,&x))
    {
        for(int i=1; i<=n; i++)
            scanf("%d",&a[i]);
        sort(a+1,a+n+1);
        printf("pos=%d\n",f(x,1,n));
    }
}
