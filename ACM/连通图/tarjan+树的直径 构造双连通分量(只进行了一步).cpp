#include<iostream>
#include<string.h>
#include<stack>
#include<vector>
#include<algorithm>
using namespace std;
const int N=200100;
const int M=2000100;
int n,m,v[M],first[M],ext[M],num,dfn[N],low[N],cnt,col[N],tot,leaf,depth[N],maxd,rt[N],all;
bool vis[N];
stack<int>s;
vector<int>ve[N];
void init()
{
    num=0,cnt=0,tot=0,leaf=0,maxd=0,all=0;
    memset(vis,false,sizeof(vis));
    memset(dfn,0,sizeof(dfn));
    memset(col,0,sizeof(col));
    memset(low,0,sizeof(low));
    memset(first,-1,sizeof(first));
    memset(depth,0,sizeof(depth));
    for(int i=1;i<=n;++i)
        ve[i].clear();
    for(int i=1; i<=n; ++i)
        rt[i]=i;
}
void add(int x,int y)
{
    v[++num]=y;
    ext[num]=first[x];
    first[x]=num;
}
void tarjan(int st,int pre)
{
    dfn[st]=low[st]=++cnt;
    s.push(st);
    vis[st]=true;
    int pre_cnt=0;
    for(int i=first[st]; ~i; i=ext[i])
    {
        int p=v[i];
        if(p==pre&&!pre_cnt)
        {
            pre_cnt++;
            continue;
        }
        if(!dfn[p])
        {
            tarjan(p,st);
            low[st]=min(low[st],low[p]);
        }
        else if(vis[p])
            low[st]=min(low[st],dfn[p]);
    }
    if(dfn[st]==low[st])
    {
        ++tot;
        int k;
        do
        {
            k=s.top();
            col[k]=tot;
            vis[k]=false;
            s.pop();
        }
        while(k!=st);
    }
}
void dfs(int st,int pre)
{
    depth[st]=depth[pre]+1;
    if(depth[st]>depth[maxd])
        maxd=st;
    rt[st]=pre;
    int k=ve[st].size();
    for(int i=0; i<k; ++i)
    {
        int p=ve[st][i];
        if(p==pre)
            continue;
        dfs(p,st);
    }
}
int LCA(int x,int y)
{
    while(x!=y)
    {
        if(depth[x]>depth[y])
            x=rt[x];
        else if(depth[x]<depth[y])
            y=rt[y];
        else
            x=rt[x],y=rt[y];
    }
    return x;
}
int main()
{
    while(cin>>n>>m)
    {
        if(!n&&!m)
            break;
        init();
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
            for(int j=first[i]; ~j; j=ext[j])
            {
                int p=v[j];
                if(col[i]!=col[p])
                {
                    ve[col[i]].push_back(col[p]);
                    all++;
                }
            }
        all/=2;
        dfs(1,1);
        int a=maxd;
        memset(depth,0,sizeof(depth));
        maxd=0;
        dfs(a,a);
        int b=maxd;
        int lca=LCA(a,b);
        int sum=0;
        while(a!=lca)
        {
            sum++;
            a=rt[a];
        }
        while(b!=lca)
        {
            sum++;
            b=rt[b];
        }
        cout<<all-sum<<endl;
    }
}
//hdu4612
