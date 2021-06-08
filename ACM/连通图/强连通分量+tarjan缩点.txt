#include<stdio.h>
#include<string.h>
#include<vector>
#include<algorithm>
#include<stack>
using namespace std;
typedef long long ll;
const ll N=100105;
const ll M=100105;
ll v[M],first[M],ext[M],num,n,m,dfn[N],low[N],cnt,col[N],tot,edgenum[N],nodenum[N],sum,edge,out[N],onode,in[N],ans;
bool vis[N];
stack<ll>s;
vector<ll>ve[N];
void init()
{
    num=cnt=tot=sum=edge=onode=ans=0;
    memset(dfn,0,sizeof(dfn));
    memset(edgenum,0,sizeof(edgenum));
    memset(out,0,sizeof(out));
    memset(in,0,sizeof(in));
    memset(nodenum,0,sizeof(nodenum));
    memset(vis,false,sizeof(vis));
    memset(low,0,sizeof(low));
    memset(col,0,sizeof(col));
    memset(first,-1,sizeof(first));
}
void add(ll x,ll y)
{
    v[++num]=y;
    ext[num]=first[x];
    first[x]=num;
}
void tarjan(ll st)
{
    dfn[st]=low[st]=++cnt;
    vis[st]=true;
    s.push(st);
    for(ll i=first[st]; ~i; i=ext[i])
    {
        ll p=v[i];
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
        ll k;
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
//    ios::sync_with_stdio(false);
//    cin.tie(0);
    ll t,cas=0;
    scanf("%lld",&t);
    while(t--)
    {
        init();
        scanf("%lld%lld",&n,&m);
        for(ll i=1; i<=m; ++i)
        {
            ll x,y;
            scanf("%lld%lld",&x,&y);
            add(x,y);
        }
        for(ll i=1; i<=n; ++i)
            if(!dfn[i])
                tarjan(i);
        if(tot==1)
        {
            printf("Case %lld: -1\n",++cas);
            continue;
        }
        for(ll i=1; i<=n; ++i)
        {
            nodenum[col[i]]++;
            for(ll j=first[i]; ~j; j=ext[j])
            {
                ll p=v[j];
                if(col[i]!=col[p])
                {
                    //ve[col[i]].push_back(col[p]);
                    edge++;
                    out[col[i]]++;
                    in[col[p]]++;
                }
                else
                    edgenum[col[i]]++;
            }
        }
        sum=n*(n-1)-m;
        for(ll i=1;i<=tot;++i)
        {
            if(!in[i]||!out[i])
            ans=max(ans,sum-nodenum[i]*(n-nodenum[i]));
        }
        printf("Case %lld: %lld\n",++cas,ans);
    }
    return 0;
}
//hdu4635
