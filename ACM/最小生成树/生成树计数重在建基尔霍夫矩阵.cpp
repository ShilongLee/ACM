#include<iostream>
#include<map>
#include<algorithm>
#include<string.h>
using namespace std;
const int N=305;
const int mod=10007;
const double eps=1e-8;
int n,r;
int x[N],y[N];
int A[N][N];
int gauss(int n)
{
    int ans=1;
    for(int i=1; i<=n; ++i)
    {
        if(!A[i][i])
        {
            bool flag=false;
            for(int j=i+1; j<=n; ++j)
            {
                if(A[j][i])
                {
                    flag=true;
                    for(int k=i; k<=n; ++k)
                        swap(A[j][k],A[i][k]);
                    ans=-ans;
                    break;
                }
            }
            if(!flag)
                return -1;
        }
        for(int j=i+1; j<=n; ++j)
        {
            while(A[j][i])
            {
                int t=A[i][i]/A[j][i];
                for(int k=i; k<=n; ++k)
                {
                    A[i][k]-=t*A[j][k];
                    A[i][k]%=mod;
                    swap(A[i][k],A[j][k]);
                }
                ans=-ans;
            }
        }
        ans*=A[i][i];
        ans%=mod;
    }
    return (ans+mod)%mod;
}
bool check(int i,int j)
{
    double k=(double)(y[i]-y[j])/(double)(x[i]-x[j]);
    for(int l=1;l<=n;++l)
    {
        if(l==i||l==j) continue;
        if(x[l]*k+(double)y[i]-k*x[i]-y[l]==0&&x[l]<=max(x[i],x[j])&&x[l]>=min(x[i],x[j]))
            return true;
    }
    return false;
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        memset(A,0,sizeof(A));
        cin>>n>>r;
        for(int i=1; i<=n; ++i)
            cin>>x[i]>>y[i];
        for(int i=1; i<=n; ++i)
        {
            int sum=0;
            for(int j=1; j<=n; ++j)
            {
                if(i!=j&&((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))<=r*r&&!check(i,j))
                {
                    A[i][j]=-1;
                    sum++;
                }
            }
            A[i][i]=sum;
        }
//        for(int i=1; i<=n; ++i)
//        {
//            for(int j=1; j<=n; ++j)
//                cout<<A[i][j]<<' ';
//            cout<<endl;
//        }
        int ans=gauss(n-1);
        cout<<ans<<endl;
    }
}
//hdu4305
