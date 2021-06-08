#include<iostream>
#include<string.h>
#include<algorithm>
#include<stack>
#include<vector>
using namespace std;
const int N=105;
const int M=10005;
int n,dfn[N],ind,tot,low[N],col[N],in[N],out[N];
bool vis[N];
stack<int>s;
vector<int>ve[N];
vector<int>ve2[N];
void tarjan(int st)
{
    dfn[st]=low[st]=++ind;
    vis[st]=true;
    s.push(st);
    for(int i=0; i<ve[st].size(); ++i)
    {
        int p=ve[st][i];
        if(!dfn[p])
        {
            tarjan(p);
            low[st]=min(low[st],low[p]);
        }
        else if(vis[p])
            low[st]=min(low[st],dfn[p]);
    }
    if(low[st]==dfn[st])
    {
        tot++;
        while(!s.empty()&&s.top()!=st)
        {
            int k=s.top();
            col[k]=tot;
            vis[k]=false;
            s.pop();
        }
        int k=s.top();
        col[k]=tot;
        vis[k]=false;
        s.pop();
    }
}
int main()
{
    memset(in,0,sizeof(in));
    memset(out,0,sizeof(out));
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(vis,false,sizeof(vis));
    ind=0,tot=0;
    cin>>n;
    for(int i=1; i<=n; ++i)
    {
        int k;
        while(cin>>k&&k)
        {
            ve[i].push_back(k);
        }
    }
    for(int i=1; i<=n; ++i)
        if(!dfn[i])
            tarjan(i);
        if(tot==1)
        {
            cout<<1<<endl;
            cout<<0<<endl;
            return 0;
        }
    for(int i=1; i<=n; ++i)
        for(int j=0; j<ve[i].size(); ++j)
        {
            if(col[i]!=col[ve[i][j]])
            {
                ve2[col[i]].push_back(col[ve[i][j]]);
            }
        }
    int ans1=0,ans2=0;
    for(int i=1; i<=tot; ++i)
    {
        out[i]+=ve2[i].size();
        for(int j=0; j<ve2[i].size(); ++j)
            in[ve2[i][j]]++;
    }
    for(int i=1; i<=tot; ++i)
    {
        if(!in[i])
            ans1++;
        if(!out[i])
            ans2++;
    }
    cout<<ans1<<endl;
    cout<<max(ans1,ans2)<<endl;
    return 0;
}
//poj1236
