#include<iostream>
#include<string.h>
#include<math.h>
#include<stdio.h>
using namespace std;
#define clr0(x) memset(x,0,sizeof(x))
#define clrm1(x) memset(x,-1,sizeof(x))
const int INF=0x3f3f3f3f;
const int maxn=55;
const int maxm=55;
const int maxnode=maxn*maxm;
int radarmapp[55];
int citymapp[55];
double distance(double x1,double y1,double x2,double y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
struct dance
{
    int n,m;
    int U[maxnode],D[maxnode],L[maxnode],R[maxnode],row[maxnode],col[maxnode];
    int H[maxn];
    int S[maxm];
    int s;
    int ans,ansed[maxn];
    void init(int _n,int _m)
    {
        n=_n;
        m=_m;
        for(int i=0; i<=m; ++i)
        {
            U[i]=D[i]=i;
            L[i]=i-1;
            R[i]=i+1;
            row[i]=0;
            col[i]=i;
            S[i]=0;
        }
        L[0]=m;
        R[m]=0;
        clrm1(H);
        clr0(ansed);
        s=m;
    }
    void push(int r,int c)
    {
        ++s;
        ++S[c];
        U[s]=c;
        D[s]=D[c];
        U[D[c]]=s;
        D[c]=s;
        row[s]=r;
        col[s]=c;
        if(H[r]<0)
            H[r]=L[s]=R[s]=s;
        else
        {
            L[s]=H[r];
            R[s]=R[H[r]];
            L[R[H[r]]]=s;
            R[H[r]]=s;
        }
    }
    void del(int c)
    {
        for(int i=D[c]; i!=c; i=D[i])
            R[L[i]]=R[i],L[R[i]]=L[i];
    }
    void roll_back(int c)
    {
        for(int i=U[c]; i!=c; i=U[i])
            R[L[i]]=L[R[i]]=i;
    }
    bool vis[maxm];
    int Astar()
    {
        int sum=0;
        for(int i=R[0]; i!=0; i=R[i])
            vis[i]=true;
        for(int i=R[0]; i!=0; i=R[i])
            if(vis[i])
            {
                sum++;
                vis[i]=false;
                for(int j=D[i]; j!=i; j=D[j])
                    for(int k=R[j]; k!=j; k=R[k])
                        vis[col[k]]=false;
            }
        return sum;
    }
    bool dancing(int step,int maxstep)
    {
        if(step+Astar()>maxstep)
            return false;
        if(R[0]==0)
            return true;
        int c=R[0];
        for(int i=R[0]; i!=0; i=R[i])
            if(S[i]<S[c])
                c=i;
        for(int i=D[c]; i!=c; i=D[i])
        {
            ansed[step]=row[i];
            del(i);
            for(int j=R[i]; j!=i; j=R[j])
                del(j);
            if(dancing(step+1,maxstep))
                return true;
            for(int j=L[i]; j!=i; j=L[j])
                roll_back(j);
            roll_back(i);
        }
        return false;
    }
};
void place(dance &dlx,double R,int n,int m)
{
    for(int i=0; i<m; ++i)
        for(int j=0; j<n; ++j)
            if(distance(radarmapp[i]/10000,radarmapp[i]%10000,citymapp[j]/10000,citymapp[j]%10000)-R<=0)
                dlx.push(i+1,j+1);
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,m,k;
        cin>>n>>m>>k;
        for(int i=0; i<n; ++i)
        {
            int x,y;
            cin>>x>>y;
            citymapp[i]=x*10000+y;
        }
        for(int i=0; i<m; ++i)
        {
            int x,y;
            cin>>x>>y;
            radarmapp[i]=x*10000+y;
        }
        double l=0,r=1500;
        while((r-l)>1e-8)
        {

            double mid=(l+r)/2;
            dance dlx;
            dlx.init(m,n);
            place(dlx,mid,n,m);
            if(dlx.dancing(0,k)) r=mid;
            else l=mid;
        }
        printf("%.6lf\n",(l+r)/2);
    }
    return 0;
}

//hdu 2295