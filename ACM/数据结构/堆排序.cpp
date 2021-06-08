#include<stdio.h>
#include<algorithm>
#include<iostream>
using namespace std;
int a[505];
void heapadjust(int start,int endd)//调整堆从start节点向下更新保证大顶堆或者小顶堆的原则
{
   int dad=start;
   int son=dad*2+1;
   while(son<=endd)
   {
       if(son+1<=endd&&a[son]<=a[son+1])
        son++;
       if(a[son]<=a[dad]) return;
       else
       {
           swap(a[dad],a[son]);
           dad=son;
           son=dad*2+1;
       }
   }
}
void heap_sort(int len)//堆排序
{
    for(int i=len/2; i>=0; i--)
        heapadjust(i,len);//自下而上建造初始堆，使最大或最小上升到第一位且符合顶堆规则
        for(int i=len;i>0;i--)//每次提出第一个节点（最大的数、最小的数）放到最后。最后得出的序列就是（升序、降序）
        {
            swap(a[0],a[i]);
            heapadjust(0,i-1);
        }
}
int main()
{
    int n;
    scanf("%d",&n);//待排序数字个数
    for(int i=0; i<n; i++)//输入待排序数组
        cin>>a[i];
    heap_sort(n-1);//堆排序
    for(int i=0; i<n; i++)//输出排序好的数组
        cout<<a[i]<<' ';
    cout<<endl;
}
