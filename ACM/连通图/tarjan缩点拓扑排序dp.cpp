#include<iostream>
#include<string.h>
#include<stack>
#include<queue>
#include<algorithm>
using namespace std;
const int N=10005;
const int M=100005;
int n,m,pointw[N],v[M],first[M],ext[M],num,dfn[N],tot,ind,low[N],col[N],w[N];
int v2[N],first2[N],ext2[N],num2,ans[N],in[N],a[N],sum;
bool vis[N];
stack<int>s;
void init()
{
    num=0,tot=0,ind=0,num2=0,sum=0;
    memset(first2,-1,sizeof(first2));
    memset(in,0,sizeof(in));
    memset(first,-1,sizeof(first));
    memset(ans,0,sizeof(ans));
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(w,0,sizeof(w));
    memset(vis,false,sizeof(vis));
}
void add(int x,int y)
{
    v[++num]=y;
    ext[num]=first[x];
    first[x]=num;
}
void add2(int x,int y)
{
    v2[++num2]=y;
    ext2[num2]=first2[x];
    first2[x]=num2;
}
void tarjan(int st)
{
    dfn[st]=low[st]=++ind;
    vis[st]=true;
    s.push(st);
    for(int i=first[st]; ~i; i=ext[i])
    {
        int p=v[i];
        if(!dfn[p])
        {
            tarjan(p);
            low[st]=min(low[st],low[p]);
        }
        else if(vis[p])
            low[st]=min(low[st],dfn[p]);
    }
    if(dfn[st]==low[st])
    {
        ++tot;
        while(s.top()!=st)
        {
            int t=s.top();
            col[t]=tot;
            vis[t]=false;
            w[tot]+=pointw[t];
            s.pop();
        }
        int t=s.top();
        col[t]=tot;
        vis[t]=false;
        w[tot]+=pointw[t];
        s.pop();
    }
}
//void dfs(int i)
//{
//    if(ans[i])
//        return ;
//    ans[i]=w[i];
//    int maxsum=0;
//    for(int j=first2[i]; ~j; j=ext2[j])
//    {
//        if(!ans[v2[j]])
//            dfs(v2[j]);
//        maxsum=max(maxsum,ans[v2[j]]);
//    }
//    ans[i]+=maxsum;
//}
void toposort()
{
    queue<int>qu;
    for(int i=1; i<=tot; ++i)
        if(!in[i])
            qu.push(i);
    while(!qu.empty())
    {
        int f=qu.front();
        qu.pop();
        a[++sum]=f;
        for(int i=first2[f]; ~i; i=ext2[i])
        {
            int p=v2[i];
            in[p]--;
            if(!in[p])
                qu.push(p);
        }
    }
}
int main()
{
    init();
    cin>>n>>m;
    for(int i=1; i<=n; ++i)
        cin>>pointw[i];
    for(int i=1; i<=m; ++i)
    {
        int x,y;
        cin>>x>>y;
        add(x,y);
    }
    for(int i=1; i<=n; ++i)
        if(!dfn[i])
            tarjan(i);
    for(int i=1; i<=n; ++i)
        for(int j=first[i]; ~j; j=ext[j])
            if(col[i]!=col[v[j]])
            {
                add2(col[i],col[v[j]]);
                in[col[v[j]]]++;
            }
    toposort();
    int res=0;
    for(int i=1; i<=sum; ++i)
    {
        int k=a[i];
        ans[k]=max(ans[k],w[k]);
        for(int j=first2[k];~j;j=ext2[j])
        {
            int p=v2[j];
            ans[p]=max(ans[p],ans[k]+w[p]);
        }
        res=max(res,ans[k]);
    }
    cout<<res<<endl;
    return 0;
}
//tarjan缩点
//洛谷3387