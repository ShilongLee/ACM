#include<stdio.h>
#include<algorithm>
#include<math.h>
#include<string.h>
#include<iostream>
using namespace std;
int table[505][505];
int f(int a)
{
    int sum=1;
    for(int i=1; i<=a; i++)
        sum*=2;
    return sum;
}
int log(int a)
{
    int sum=0;
    while(a)
    {
        if(a%2==0)
            sum++;
        a/=2;
    }
    return sum;
}
void retable(int n,int m)
{
    if(m==log(n)+1)
        return ;
    for(int i=f(m-1)+1; i<=f(m); i++)
    {
        for(int j=1; j<=n; j++)
        {
            if(((j-1)/(f(m)/2))%2==0)
                table[i][j]=table[i-f(m)/2][j+f(m)/2];
            else
                table[i][j]=table[i-f(m)/2][j-f(m)/2];
        }
    }
    retable(n,m+1);
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int j=1; j<=n; j++)
        table[1][j]=j;
    retable(n,1);
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
            printf("%d ",table[i][j]);
        printf("\n");
    }
}
