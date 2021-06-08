#include<stdio.h>
#include<algorithm>
#include<iostream>
using namespace std;
int a[500500];
int Max(int a[],int l,int r)
{
    int x=a[l];
    for(int i=l; i<r; i++)
        if(a[i]>x)
            x=a[i];
    return x;
}
int Min(int a[],int l,int r)
{
    int x=a[l];
    for(int i=l; i<r; i++)
        if(a[i]<x)
            x=a[i];
    return x;
}
int Partition(int a[],int l,int r,int x)
{
    int i=l-1,j=r+1;
    while(1)
    {
        while(a[++i]<x&&i<r);
        while(a[--j]>x);
            if(i>=j)
                break;
        swap(a[i],a[j]);
    }
    return i;
}
int cpair(int l,int r)
{
    if(r-l<1) return 9999999;//返回9999999，单个点的距离为无限。
    int  m1=Max(a,l,r),m2=Min(a,l,r);
    int m=(m1+m2)/2;
    int j=Partition(a,l,r,m);
    int d1=cpair(l,j),d2=cpair(j+1,r);
    int d3=Min(a,j+1,r)-Max(a,l,j);
    return min(d1,min(d2,d3));
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1; i<=n; i++)
        scanf("%d",&a[i]);
        int p=cpair(1,n);
        printf("%d\n",p);
}
