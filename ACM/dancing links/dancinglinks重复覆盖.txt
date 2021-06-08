#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;
#define clr0(x) memset(x,0,sizeof(x))
#define clrm1(x) memset(x,-1,sizeof(x))
const int N=20;
const int M=20;
const int maxn=N*M+10;
const int maxm=N*M+10;
const int maxnode=maxn*maxm;
const int INF=0x3f3f3f3f;
int mapp[N][M];
struct dance
{
    int n,m;
    int U[maxnode],D[maxnode],L[maxnode],R[maxnode],row[maxnode],col[maxnode];
    int H[maxn];
    int S[maxm];
    int s;
    int ansed,ans[maxn];
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
        s=m;
        R[m]=0;
        L[0]=m;
        clrm1(H);
        clr0(ans);
        ansed=INF;
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
    void dancing(int step)
    {
        if(step+Astar()>=ansed)
            return;
        if(R[0]==0)
        {
            ansed=min(ansed,step);
            return ;
        }
        int c=R[0];
        for(int i=R[0]; i!=0; i=R[i])
            if(S[i]<S[c])
                c=i;
        for(int i=D[c]; i!=c; i=D[i])
        {
            ans[step]=row[i];
            del(i);
            for(int j=R[i]; j!=i; j=R[j])
                del(j);
            dancing(step+1);
            for(int j=L[i]; j!=i; j=L[j])
                roll_back(j);
            roll_back(i);
        }
    }
} dlx;
int main()
{
    int n,m;
    while(cin>>n>>m)
    {
        int sum=0;
        for(int i=0; i<n; ++i)
            for(int j=0; j<m; ++j)
            {
                cin>>mapp[i][j];
                if(mapp[i][j])
                    mapp[i][j]=++sum;
            }
        int n1,m1;
        cin>>n1>>m1;
        dlx.init(n*m,sum);
        for(int i=0; i<n; ++i)
            for(int j=0; j<m; ++j)
                for(int sn=0; sn<n1&&i+sn<n; ++sn)
                    for(int sm=0; sm<m1&&j+sm<m; ++sm)
                    {
                        if(mapp[i+sn][j+sm]>0)
                        {
                            //cout<<i*n+j+1<<' '<<mapp[i+sn][j+sm]<<endl;
                            dlx.push(i*m+j+1,mapp[i+sn][j+sm]);
                        }
                    }
        dlx.dancing(0);
        cout<<dlx.ansed<<endl;
    }
    return 0;
}

//FZU 1686