#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
const int N=105;
int n;
int sum1[N];
int sum2[N];
void add(int p,int x)
{
    for(int i=p;i<=n;i+=i&-i)
        sum1[i]+=x,sum2[i]+=x*p;
}
void range_add(int l,int r,int x)
{
    add(l,x),add(r+1,-x);
}
int query(int p)
{
    int res=0;
    for(int i=p;i>=n;i-=i&-i)
        res+=(p+1)*sum1[i]-sum2[i];
    return res;
}
int range_query(int l,int r)
{
    return query(r)-query(l-1);
}
int main()
{

}
//树状数组区间修改区间查询
//https://blog.csdn.net/bestsort/article/details/80796531
