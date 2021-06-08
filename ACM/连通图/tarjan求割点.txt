#include<string.h>
#include<algorithm>
#include<stack>
#include<iostream>
using namespace std;
const int N=20005;
const int M=200005;
int v[M],first[M],ext[M],num,dfn[N],low[N],cnt,sum;
bool vis[N];
void add(int x,int y)
{
    v[++num]=y;
    ext[num]=first[x];
    first[x]=num;
}
void tarjan(int st,int pre)
{
    dfn[st]=low[st]=++cnt;
    int child=0;
    for(int i=first[st]; ~i; i=ext[i])
    {
        int p=v[i];
        if(p==pre)
            continue;
        if(!dfn[p])
        {
            tarjan(p,st);
            low[st]=min(low[st],low[p]);
            if(st==pre)
                child++;
            if(low[p]>=dfn[st]&&st!=pre)
                vis[st]=true;
        }
        else
            low[st]=min(low[st],dfn[p]);
    }
    if((child>1&&st==pre))
        vis[st]=true;
}
int main()
{
    int n,m;
    num=0,cnt=0,sum=0;
    memset(dfn,0,sizeof(dfn));
    memset(vis,false,sizeof(vis));
    memset(low,0,sizeof(vis));
    memset(first,-1,sizeof(first));
    cin>>n>>m;
    for(int i=1; i<=m; ++i)
    {
        int x,y;
        cin>>x>>y;
        add(x,y);
        add(y,x);
    }
    for(int i=1; i<=n; ++i)
        if(!dfn[i])
            tarjan(i,i);
    for(int i=1; i<=n; ++i)
        if(vis[i])
            sum++;
    cout<<sum<<endl;
    for(int i=1; i<=n; ++i)
        if(vis[i])
            cout<<i<<' ';
    cout<<endl;
    return 0;
}
//tarjan求割点
//洛谷3388
