#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<iostream>
using namespace std;
int a[500500];
int Partition(int a[],int l,int r,int x)
{
    int pos;
    for(int i=l;i<r;i++)
        if(a[i]==x) pos=i;
    swap(a[l],a[pos]);
    int i=l,j=r;
    while(1)
    {
        while(a[++i]<x&&i<r);
        while(a[--j]>x);
            if(i>=j)
                break;
        swap(a[i],a[j]);
    }
    swap(a[l],a[j]);
    return j;
}
int select(int a[],int p,int r,int k)
{
    if(r-p<75)
    {
        sort(a+p,a+r);
        return a[p+k-1];
    }
    for(int i=0; i<(r-p-4)/5; i++)
    {
        sort(a+p+5*i,a+p+5*i+5);
        swap(a[p+5*i+2],a[p+i]);
    }
    int x=select(a,p,p+(r-p-4)/5,(r-p-4)/10);
    int i=Partition(a,p,r,x);
    int j=i-p+1;
    if(k<=j)
        return select(a,p,i,k) ;
    else
        return select(a,i+1,r,k-j);
}
int main()
{
    for(int i=0; i<15000; i++)
        a[i]=15000-i;
    int p=select(a,0,15000,13300);
          printf("%d\n",p);
}
