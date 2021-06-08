#include<stdio.h>
#include<string.h>
#include<queue>
#include<functional>
#include<math.h>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=205;
int dis[N];
int v[80005],w[80005],first[80005],ext[80005],num;
int n;
int x[50005];
int y[50005];
int vis[N];
typedef pair<int,int>pii;
void add(int x,int y,int z)
{
    v[++num]=y;
    w[num]=z;
    ext[num]=first[x];
    first[x]=num;
}
double Prim(int st,int &sum)
{
    memset(dis,inf,sizeof(dis));
    dis[st]=0;
    memset(vis,0,sizeof(vis));
    double ans=0;
    priority_queue<pii,vector<pii>,greater<pii> >qu;
    qu.push(make_pair(0,st));
    while(!qu.empty())
    {
        pii f=qu.top();
        qu.pop();
        if(vis[f.second])
            continue;
        vis[f.second]=1;
        ans+=sqrt(double(f.first))*100;
        sum++;
        for(int i=first[f.second]; i!=-1; i=ext[i])
        {
            int pos=v[i];
            if(!vis[pos]&&dis[pos]>w[i]&&w[i]<=1000000&&w[i]>=100)
            {
                dis[pos]=w[i];
                qu.push(make_pair(w[i],pos));
            }
        }
    }
    return ans;
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        memset(first,-1,sizeof(first));
        num=0;
        scanf("%d",&n);
        for(int i=1; i<=n; ++i)
        {
            scanf("%d%d",&x[i],&y[i]);
            for(int j=1; j<=i; ++j)
                if(i!=j)
                {
                    int d=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
                    add(i,j,d);
                    add(j,i,d);
                }
        }
        int edge=0;
        double ans=Prim(1,edge);
        if(edge<n)
            printf("oh!\n");
        else
            printf("%.1lf\n",ans);
    }
}
//hdu1875