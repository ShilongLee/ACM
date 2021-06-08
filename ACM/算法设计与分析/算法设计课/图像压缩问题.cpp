#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<iostream>
using namespace std;
int s[5005];
int l[505];
int b[505];
int p[505];
int log(int n)
{
    int sum=0;
    while(n)
    {
        sum++;
        n/=2;
    }
    return sum;
}
void Compress(int n)
{
    int Lmax=256,header=11;
    s[0]=0;
    for(int i=1; i<=n; i++)
    {
        b[i]=log(p[i]);
        int bmax=b[i];
        s[i]=s[i-1]+bmax+header;
        l[i]=1;
        for(int j=2; j<=i&&j<=Lmax; j++)
        {
            bmax=max(bmax,log(p[i-j+1]));
            if(s[i]>s[i-j]+bmax*j+header)
            {
                s[i]=s[i-j]+bmax*j+header;
                l[i]=j;
                b[i]=bmax;
            }
        }
    }
}
void Tb(int n)
{
    if(n==0) return ;
    Tb(n-l[n]);
    printf("%d~%d\n",n-l[n]+1,n);
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1; i<=n; i++)
        scanf("%d",&p[i]);
    Compress(n);
    printf("%d\n",s[n]);
    Tb(n);
}
