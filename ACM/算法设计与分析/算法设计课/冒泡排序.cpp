#include<stdio.h>
#include<algorithm>
#include<time.h>
#include<windows.h>
using namespace std;
int a[5005];
void BubbleSort(int a[],int l,int r)
{
    for(int i=l; i<=r; i++)
    {
        for(int j=l; j<r; j++)
        {
            if(a[j]>a[j+1])
                swap(a[j],a[j+1]);
        }
    }
}
int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        for(int i=1; i<=n; i++)
            scanf("%d",&a[i]);
        double time,time_end,time_start;
        time_start=GetTickCount();
        BubbleSort(a,1,n);
        time_end=GetTickCount();
        time=time_end-time_start;
        for(int i=1; i<=n; i++)
            printf("%d ",a[i]);
        printf("\n");
        printf("运行时间:%.3lfms\n",time);

    }
}
