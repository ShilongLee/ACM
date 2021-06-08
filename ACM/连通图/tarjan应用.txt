#include<iostream>
#include<algorithm>
#include<string.h>
#include<vector>
#include<queue>
using namespace std;
const int N=10005;
const int M=50005;
int n,m,dfn[N],low[N],cnt,tot,top,s[N],col[N],num[N],in[N],out[N],a[N],t,dp[N];
bool vis[N];
vector<int>ve1[N];
vector<int>ve2[N];
void tarjan(int st)
{
    dfn[st]=low[st]=++cnt;
    vis[st]=true;
    s[++top]=st;
    for(int i=0; i<ve1[st].size(); ++i)
    {
        if(!dfn[ve1[st][i]])
        {
            tarjan(ve1[st][i]);
            low[st]=min(low[st],low[ve1[st][i]]);
        }
        else if(vis[ve1[st][i]])
            low[st]=min(low[st],dfn[ve1[st][i]]);
    }
    if(dfn[st]==low[st])
    {
        ++tot;
        while(s[top+1]!=st)
        {
            col[s[top]]=tot;
            num[tot]+=1;
            vis[s[top]]=false;
            --top;
        }
    }
}
void topo()
{
    queue<int>qu;
    for(int i=1; i<=tot; ++i)
        if(!in[i])
            qu.push(i);
    while(!qu.empty())
    {
        int f=qu.front();
        qu.pop();
        a[++t]=f;
        for(int i=0; i<ve2[f].size(); ++i)
        {
            in[ve2[f][i]]--;
            if(!in[ve2[f][i]])
                a[++t]=ve2[f][i];
        }
    }
}
int main()
{
    cnt=0,tot=0,top=0,t=0;
    memset(dfn,0,sizeof(dfn));
    memset(dp,0,sizeof(dp));
    memset(out,0,sizeof(out));
    memset(in,0,sizeof(in));
    memset(num,0,sizeof(num));
    memset(low,0,sizeof(low));
    memset(vis,false,sizeof(vis));
    cin>>n>>m;
    for(int i=1; i<=m; ++i)
    {
        int x,y;
        cin>>x>>y;
        ve1[x].push_back(y);
    }
    for(int i=1; i<=n; ++i)
        if(!dfn[i])
            tarjan(i);
    for(int i=1; i<=n; ++i)
        for(int j=0; j<ve1[i].size(); ++j)
            if(col[i]!=col[ve1[i][j]])
            {
                ve2[col[i]].push_back(col[ve1[i][j]]);
                out[col[i]]++;
                in[col[ve1[i][j]]]++;
            }
    int flag=0,ans;
    for(int i=1; i<=tot; ++i)
        if(!out[i])
        {
            flag++;
            ans=num[i];
        }
    if(flag==1)
        cout<<ans<<endl;
    else
        cout<<0<<endl;
}
//洛谷2341
