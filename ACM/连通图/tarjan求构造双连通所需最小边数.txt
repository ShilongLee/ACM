#include<iostream>
#include<string.h>
#include<stack>
#include<vector>
#include<algorithm>
using namespace std;
const int N=10005;
const int M=30005;
int n,m,v[M],first[M],ext[M],num,dfn[N],low[N],cnt,col[N],tot,leaf;
bool vis[N];
stack<int>s;
vector<int>ve[N];
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
int main()
{
    num=0,cnt=0,tot=0,leaf=0;
    memset(vis,false,sizeof(vis));
    memset(dfn,0,sizeof(dfn));
    memset(col,0,sizeof(col));
    memset(low,0,sizeof(low));
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
        for(int j=first[i]; ~j; j=ext[j])
        {
            int p=v[j];
            if(col[i]!=col[p])
                ve[col[i]].push_back(col[p]);
        }
    for(int i=1; i<=tot; ++i)
            if(ve[i].size()==1) leaf++;
    cout<<(leaf+1)/2<<endl;
}
//poj3177
