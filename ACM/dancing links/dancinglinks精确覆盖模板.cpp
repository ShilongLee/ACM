#include<bits/stdc++.h>
using namespace std;
#define clr0(x) memset(x,0,sizeof(x))
#define clrm1(x) memset(x,-1,sizeof(x))
#define maxnode 1000010
#define maxn 1010
struct DL
{
    int n,m;
    int U[maxnode],D[maxnode],L[maxnode],R[maxnode],row[maxnode],col[maxnode];
    int H[maxn];
    int S[maxn];
    int ansed;
    int ans[maxn],s;
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
            col[i]=i;
            row[i]=0;
        }
        L[0]=m;
        R[m]=0;
        s=m;
        clrm1(H);
        clr0(ans);
        ansed=0;
    }
    void push(int r,int c)
    {
        s++;
        U[s]=c;
        D[s]=D[c];
        U[D[c]]=s;
        D[c]=s;
        row[s]=r;
        col[s]=c;
        if(H[r]<0)
        {
            H[r]=s;
            R[s]=L[s]=s;
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
            }
    }
    void reback(int c)
    {
        for(int i=U[c]; i!=c; i=U[i])
            for(int j=L[i]; j!=i; j=L[j])
            {
                D[U[j]]=j;
                U[D[j]]=j;
            }
        L[L[c]]=c;
        R[R[c]]=c;
    }
    bool dancing(int step)
    {
        if(R[0]==0)
        {
            ansed=step;
            return true;
        }
        int c=R[0];
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
int main()
{
    int n,m;
    while(cin>>n>>m)
    {
        dlx.init(n,m);
        for(int i=1; i<=n; i++)
        {
            int num;
            cin>>num;
            for(int j=0; j<num; j++)
            {
                int a;
                cin>>a;
                dlx.push(i,a);
            }
        }
        if(dlx.dancing(0))
        {
            cout<<dlx.ansed<<' ';
            for(int i=0; i<dlx.ansed; ++i)
                cout<<dlx.ans[i]<<' ';
            cout<<endl;
        }
        else
            cout<<"NO"<<endl;
    }
}

//HUST1017
