#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
const int N=1005;
const int M=N*N*2;
const int inf=0x3f3f3f3f;
int n,m,v[M],w[M],first[M],ext[M],num,dfn[N],low[N],cnt,ans,sum;
void init()
{
    num=cnt=sum=0;
    ans=inf;
    memset(dfn,0,sizeof(dfn));
    memset(w,0,sizeof(w));
    memset(low,0,sizeof(low));
    memset(first,-1,sizeof(first));
}
void add(int x,int y,int z)
{
    v[++num]=y;
    w[num]=z;
    ext[num]=first[x];
    first[x]=num;
}
void tarjan(int st,int pre)
{
    dfn[st]=low[st]=++cnt;
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
            if(low[p]>dfn[st])
                ans=min(ans,w[i]);
        }
        else
            low[st]=min(low[st],dfn[p]);
    }
}
int main()
{
    while(cin>>n>>m&&(n||m))
    {
        init();
        for(int i=1; i<=m; ++i)
        {
            int x,y,z;
            cin>>x>>y>>z;
            add(x,y,z);
            add(y,x,z);
        }
        for(int i=1; i<=n; ++i)
            if(!dfn[i])
            {
                tarjan(i,i);
                sum++;
            }
        if(sum>1)
            cout<<0<<endl;
        else if(ans==inf)
            cout<<-1<<endl;
        else
            cout<<(ans==0?1:ans)<<endl;
    }
}
//hdu4738
