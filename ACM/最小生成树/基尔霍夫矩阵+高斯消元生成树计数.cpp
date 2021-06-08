#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
const long long N=55;
long long A[N][N];
long long B[N][N];
long long n,m,k;
void print()
{
    for(long long i=1; i<=n-1; ++i)
    {
        for(long long j=1; j<=n-1; ++j)
        {
            cout<<B[i][j]<<' ';
        }
        cout<<endl;
    }
    cout<<endl;
}
long long gauss(long long n)
{
    long long ans=1;
    for(long long i=1; i<=n; ++i)
    {
        bool flag=false;
        if(!B[i][i])
        {
            for(long long j=i+1; j<=n; ++j)
            {
                if(B[j][i])
                {
                    flag=true;
                    for(long long k=i; k<=n; ++k)
                        swap(B[i][k],B[j][k]);
                        ans=-ans;
                        break;
                }
            }
            if(!flag)
                return 0;
        }
        for(long long j=i+1; j<=n; ++j)
        {
            while(B[j][i])
            {
                long long t=B[i][i]/B[j][i];
                for(long long k=i; k<=n; ++k)
                {
                    B[i][k]-=t*B[j][k];
                    swap(B[i][k],B[j][k]);
                }
                ans=-ans;
            }
        }
        ans*=B[i][i];
       // print();
    }
    return ans;
}
int main()
{
    while(cin>>n>>m>>k)
    {
        memset(B,0,sizeof(B));
        memset(A,0,sizeof(A));
        for(long long i=1; i<=m; ++i)
        {
            long long x,y;
            cin>>x>>y;
            A[x][y]=A[y][x]=1;
        }
        for(long long i=1; i<=n; ++i)
            for(long long j=1; j<=n; ++j)
                if(!A[i][j]&&i!=j)
                {
                    B[i][i]+=1;
                    B[i][j]=-1;
                }
                //print();
        long long ans=gauss(n-1);
        cout<<ans<<endl;
    }
}
//UVA - 10766
