#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<iostream>
using namespace std;
const long long N=333;
long long n,mod;
long long A[N][N];
long long gauss(long long n)
{
    long long ans=1;
    for(long long i=1; i<=n; ++i)
    {
        if(!A[i][i])
        {
            bool flag=false;
            for(long long j=i+1; j<=n; ++j)
            {
                if(A[j][i])
                {
                    flag=true;
                    for(long long k=i; k<=n; ++k)
                        swap(A[i][k],A[j][k]);
                    ans=-ans;
                    break;
                }
            }
            if(!flag)
                return 0;
        }
        for(long long j=i+1; j<=n; ++j)
        {
            while(A[j][i])
            {
                long long t=A[i][i]/A[j][i];
                for(long long k=i; k<=n; ++k)
                {
                    A[i][k]=(A[i][k]-(t*A[j][k]))%mod;
                    swap(A[i][k],A[j][k]);
                }
                ans=-ans;
            }
        }
        ans=(ans*A[i][i])%mod;
    }
    return (ans+mod)%mod;
}
int main()
{
    while(cin>>n>>mod)
    {
        for(long long i=1; i<=n; ++i)
            for(long long j=1; j<=n; ++j)
            {
                long long a;
                scanf("%lld",&a);
                A[i][j]=a%mod;
            }
//        for(int i=1; i<=n; ++i)
//        {
//            for(int j=1; j<=n; ++j)
//                printf("%lld ",A[i][j]);
//                printf("\n");
//        }
//        printf("\n");
        long long ans=gauss(n);
        //if(ans<0) ans=-ans;
        printf("%lld\n",ans);
    }
    return 0;
}
//SPOJ - DETER3
