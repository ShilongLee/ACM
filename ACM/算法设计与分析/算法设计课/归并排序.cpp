#include<stdio.h>
#include<algorithm>
#include<time.h>
#include<string.h>
#include<windows.h>
using namespace std;
int a[5000005];
int b[5000005];
void Merge(int a[],int b[],int l,int mid,int r)//排序到b数组
{
    int i=l,j=mid+1,k=l;
    while(i<=mid&&j<=r)
    {
        if(a[i]<=a[j]) b[k++]=a[i++];
        else b[k++]=a[j++];
    }
    if(i>mid) for(int q=j; q<=r; q++) b[k++]=a[q];
    else for(int q=i; q<=mid; q++) b[k++]=a[q];
}
void Mergepass(int a[],int b[],int s,int n)//归并复制
{
    int i=0;
    for( i=0; i<=n-s*2; i+=s*2)
        Merge(a,b,i,i+s-1,i+s*2-1);
    if(i+s<n) Merge(a,b,i,i+s-1,n-1);
    else for(int j=i; j<n; j++) b[j]=a[j];
}
void Mergesort(int a[],int r)//归并排序
{
    int s=1;
    while(s<r)
    {
        Mergepass(a,b,s,r);
        s+=s;
        Mergepass(b,a,s,r);
        s+=s;
    }
}
int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        double time,time_end,time_start;
        for(int i=0; i<n; i++)
            scanf("%d",&a[i]);
        time_start=GetTickCount();
        Mergesort(a,n);
        time_end=GetTickCount();
        time=time_end-time_start;
        for(int i=0;i<n;i++)
            printf("%d ",a[i]);
        printf("\n");
        printf("运行时间：%.3lfms\n",time);
        printf("\n");
    }
    return 0;
}
