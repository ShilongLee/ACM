#include<stdio.h>
#include<iostream>
using namespace std;
int q(int n,int m)
{
    if(m==1)
    return 1;
    if(n<m)
        return q(n,n);
    if(n==m)
        return 1+q(n,n-1);
    if(n>m&&m>1)
        return q(n,m-1)+q(n-m,m);
}
int main()
{
    cout<<q(2021,6)<<endl;
}
