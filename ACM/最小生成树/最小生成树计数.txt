#include<iostream>
#include<algorithm>
#include<string.h>
#include<vector>
using namespace std;
const int M=1005;
const int N=105;
const int mod=31011;
struct Edge
{
    int x,y,len;
    bool operator<(const Edge &a)const
    {
        return len<a.len;
    }
} MST[M],edge[M];
int rt[N],n,m,RT[N];
int A[N][N];
vector<Edge>E[M];
bool vis[M];
int fin(int x)
{
    if(rt[x]==x)
        return x;
    return rt[x]=fin(rt[x]);
}
void init()
{
    for(int i=1; i<=n; ++i)
        rt[i]=i;
}
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
                        swap(A[i][k],A[j][k]);
                    ans=-ans;
                    break;
                }
            }
            if(!flag)
                return 0;
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
        ans=ans*A[i][i]%mod;
    }
    return (ans+mod)%mod;
}
int main()
{
    int temp=0,kind=0,cnt=0;
    cin>>n>>m;
    init();
    memset(vis,false,sizeof(vis));
    memset(A,0,sizeof(A));
    for(int i=1; i<=m; ++i)
        cin>>edge[i].x>>edge[i].y>>edge[i].len;
    sort(edge+1,edge+m+1);
    for(int i=1; i<=m; ++i)
    {
        if(temp!=edge[i].len)
            kind++,temp=edge[i].len;
        E[kind].push_back(edge[i]);
        int xx=fin(edge[i].x);
        int yy=fin(edge[i].y);
        if(xx!=yy)
        {
            vis[kind]=true;
            rt[xx]=yy;
            MST[++cnt]=edge[i];
            MST[cnt].len=kind;
        }
    }
    if(cnt!=n-1)
    {
        cout<<0<<endl;
        return 0;
    }
//    for(int i=1; i<=cnt; ++i)
//        cout<<MST[i].x<<MST[i].y<<endl;
    int ans=1;
    for(int i=1; i<=kind; ++i)
    {
        if(!vis[i])
            continue;
        int siz=E[i].size();
        init();
        int knt=0;
        for(int j=1; j<=cnt; ++j)
        {
            if(MST[j].len==i)
                continue;
            int xx=fin(MST[j].x);
            int yy=fin(MST[j].y);
            rt[xx]=yy;
        }
//        for(int j=1; j<=n; ++j)
//            cout<<rt[j];
        for(int j=1; j<=n; ++j)
            if(fin(j)==j)
                RT[j]=++knt;
        for(int j=1; j<=n; ++j)
            RT[j]=RT[fin(j)];
//        for(int j=1; j<=n; ++j)
//            cout<<RT[j];
        for(int j=0; j<siz; ++j)
        {
            int xx=RT[E[i][j].x],yy=RT[E[i][j].y];
            A[xx][yy]-=1;
            A[yy][xx]-=1;
            A[xx][xx]++;
            A[yy][yy]++;
        }
        ans=ans*gauss(knt-1)%mod;
        for(int j=1; j<=knt; ++j)
        {
            for(int k=1; k<=knt; ++k)
                A[j][k]=0;
        }
//        for(int k=1; k<=knt; ++k)
//        {
//            for(int j=1; j<=knt; ++j)
//                cout<<A[k][j]<<' ';
//            cout<<endl;
//        }
    }
    cout<<ans<<endl;
    return 0;
}
//洛谷4208
