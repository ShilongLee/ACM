#include<iostream>
#include<stdio.h>
#include<string.h>
#include<string.h>
using namespace std;
long long mapp[15][15];
long long A[155][155];
long long n,m;
const long long mod=1000000000;
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
                    A[i][k]-=t*A[j][k];
                    A[i][k]%=mod;
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
    cin>>n>>m;
    char c;
    long long cnt=0;
    memset(A,0,sizeof(A));
    for(long long i=1; i<=n; ++i)
        for(long long j=1; j<=m; ++j)
        {
            scanf(" %c",&c);
            if(c=='.')
                mapp[i][j]=++cnt;
            else
                mapp[i][j]=-1;
        }
    for(long long i=1; i<=n; ++i)
        for(long long j=1; j<=m; ++j)
        {
            if(mapp[i][j]==-1)
                continue;
            if(j+1<=m&&mapp[i][j+1]!=-1)
                A[mapp[i][j]][mapp[i][j+1]]=A[mapp[i][j+1]][mapp[i][j]]=-1;
            if(i+1<=n&&mapp[i+1][j]!=-1)
                A[mapp[i+1][j]][mapp[i][j]]=A[mapp[i][j]][mapp[i+1][j]]=-1;
        }
    for(long long i=1; i<=cnt; ++i)
    {
        long long sum=0;
        for(long long j=1; j<=cnt; ++j)
        {
            if(A[i][j])
                sum=(sum+1)%mod;
        }
        A[i][i]=sum%mod;
    }
//    for(long long i=1; i<=cnt; ++i)
//    {
//        for(long long j=1; j<=cnt; ++j)
//            cout<<A[i][j]<<' ';
//        cout<<endl;
//    }
    long long ans=gauss(cnt-1);
    cout<<ans<<endl;
    return 0;
}
//URAL - 1627
