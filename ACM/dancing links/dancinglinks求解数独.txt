#include<iostream>
#include<string.h>
using namespace std;
#define clr0(x) memset(x,0,sizeof(x))
#define clrm1(x) memset(x,-1,sizeof(x))
const int N=16;
const int maxn= N*N*N+10;
const int maxm=N*N*4+10;
const int maxnode=maxn*4+maxm+10;
char mapp[N*N+10];
struct dlx
{
    int n,m;
    int U[maxnode],D[maxnode],L[maxnode],R[maxnode];
    int H[maxn];
    int S[maxm];
    int ansed,ans[maxn];
    int s;
    int row[maxnode],col[maxnode];
    void init(int _n,int _m)
    {
        n=_n;
        m=_m;
        for(int i=0; i<=m; ++i)
        {
            U[i]=D[i]=i;
            L[i]=i-1;
            R[i]=i+1;
            S[i]=0;
            row[i]=0;
            col[i]=i;
        }
        L[0]=m;
        R[m]=0;
        clrm1(H);
        clr0(ans);
        s=m;
    }
    void push(int r,int c)
    {
        ++S[c];
        ++s;
        U[s]=c;
        D[s]=D[c];
        U[D[c]]=s;
        D[c]=s;
        row[s]=r;
        col[s]=c;
        if(H[r]<0)
        {
            H[r]=s;
            L[s]=R[s]=s;
        }
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
        R[L[c]]=R[c];
        L[R[c]]=L[c];
        for(int i=D[c]; i!=c; i=D[i])
            for(int j=R[i]; j!=i; j=R[j])
            {
                D[U[j]]=D[j];
                U[D[j]]=U[j];
                S[col[j]]--;
            }
    }
    void reback(int c)
    {
        for(int i=U[c]; i!=c; i=U[i])
            for(int j=L[i]; j!=i; j=L[j])
            {
                D[U[j]]=j;
                U[D[j]]=j;
                S[col[j]]++;
            }
        R[L[c]]=L[R[c]]=c;
    }
    bool dancing(int step)
    {
        if(R[0]==0)
        {
            for(int i=0; i<step; ++i)
                mapp[(ans[i]-1)/N]=(ans[i]-1)%N+'A';
            for(int j=0; j<N*N; ++j)
            {
                if(!(j%16)&&j>0)
                    cout<<endl;
                cout<<mapp[j];
            }
            cout<<endl;
            return true;
        }
        int c=R[0];
        for(int i=R[0]; i!=0; i=R[i])
            if(S[i]<S[c])
                c=i;
        del(c);
        for(int i=D[c]; i!=c; i=D[i])
        {
            ans[step]=row[i];
            for(int j=R[i]; j!=i; j=R[j])
                del(col[j]);
            if(dancing(step+1))
                return true;
            for(int j=L[i]; j!=i; j=L[j])
                reback(col[j]);
        }
        reback(c);
        return false;
    }
} dlx;
void place(int &r,int &c1,int &c2,int &c3,int &c4,int i,int j,int k)
{
    r=(i*N+j)*N+k;
    c1=i*N+j+1;
    c2=N*N+i*N+k;
    c3=N*N*2+j*N+k;
    c4=N*N*3+((i/4)*4+j/4)*N+k;
}
int main()
{
    int a=0;
    while(cin>>mapp)
    {
        int sum=0;
        for(int i=1; i<16; ++i)
            for(int j=0; j<16; ++j)
                cin>>mapp[i*N+j];
        /* for(int i=0; i<16; ++i)
        for(int j=0; j<16; ++j)
        if(mapp[i*N+j]!='-') sum++;
        cout<<sum;*/
        dlx.init(N*N*N,N*N*4);
        int r,c1,c2,c3,c4;
        for(int i=0; i<N; ++i)
            for(int j=0; j<N; ++j)
                for(int k=1; k<=N; k++)
                {
                    if(mapp[i*N+j]=='-'||mapp[i*N+j]=='A'+k-1)
                    {
                        place(r,c1,c2,c3,c4,i,j,k);
                        dlx.push(r,c1);
                        dlx.push(r,c2);
                        dlx.push(r,c3);
                        dlx.push(r,c4);
                    }
                }
                if(++a!=1) cout<<endl;
        dlx.dancing(0);
    }
    return 0;
}

//ZOJ 3122