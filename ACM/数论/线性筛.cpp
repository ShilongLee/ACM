#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;
int is_prime[5005];//用来标记是否为素数，开始全是1，慢慢用线性筛把合数筛成0。1为素数，0为合数。
int prime[5005];//数组用来装素数
int sum=0;//统计累计有多少个素数
void f(int n)//线性筛函数（O(n)）；
{
    for(int i=2;i<=n;i++)//从二开始筛选并且不断地筛掉所有质数的i倍并且只用最小质约数筛选
    {
        if(is_prime[i]) prime[++sum]=i;//把素数放进数组里面
        for(int j=1;j<=sum&&i*prime[j]<=n;j++)//让素数数组里面的每一个素数和i相乘，i从2到n；
        {
            is_prime[i*prime[j]]=0;//也可以换成is_prime[i*prime[j]]-=1;可以查看筛了多少遍，因为起始值都是1，如果筛选了1遍以上就会减成负数。这样可以验证写的素数筛是否正确。
            if(i%prime[j]==0)//只用最小质约数筛选，比如prime：2，3，5，7，11...，此时i是8，8%2==0，所以直接break，因为所有能被8筛掉的数都可以被2筛掉。如果不break,3*8,5*8,6*8筛选一遍，到时候还会被2*(3*4),2*(5*4),2*(6*4)筛选掉，所以及时break可以让合数保证被最小质约数筛掉。
                break ;
        }
    }
}
int main()
{
    int n;
    while(cin>>n)
    {
        sum=0;
        memset(prime,0,sizeof(prime));//初始化素数数组
        for(int i=2;i<=n;i++)//刚开始所有数都设为素数，然后慢慢筛掉.
            is_prime[i]=1;
        f(n);
        for(int i=1;i<=sum;i++)//输出所有素数
            printf("%d ",prime[i]);
            printf("\n");
    }
}
