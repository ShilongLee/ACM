#include<stdio.h>
#include<algorithm>
#include<windows.h>
using namespace std;
int a[500005];
int n;
Quiksort(int l,int r)
{
    if(l<r)
    {
        int i=l,j=r;
        while(1)
        {
            while(a[++i]<a[l]&&i<r);
            while(a[--j]>a[l]);
            if(i>=j)
                break;
            swap(a[i],a[j]);
        }
        swap(a[l],a[j]);
        Quiksort(l,j);
        Quiksort(j+1,r);
    }
}
int main()
{
    while(~scanf("%d",&n))
    {
        double time,time_end,time_start;
        for(int i=0; i<n; i++)
            scanf("%d",&a[i]);
        time_start=GetTickCount();
        Quiksort(0,n);
        time_end=GetTickCount();
        time=time_end-time_start;
        for(int i=0; i<n; i++)
            printf("%d ",a[i]);
        printf("\n");
        printf("运行时间：%.3lfms\n",time);
        printf("\n");
    }
}
