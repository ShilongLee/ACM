#include<stdio.h>
#include<string.h>
#include<stack>
#include<algorithm>
using namespace std;
const int N=4005;
const int M=210000;
int n,v[M],first[M],ext[M],num,dfn[M],low[M],col[M],cnt,tot,ans[M];
bool vis[M];
stack<int>s;
void tarjan(int st,int pre)
{
    dfn[st]=low[st]=++cnt;
    vis[st]=true;
    s.push(st);
    for(int i=first[st]; ~i; i=ext[i])
    {
        int p=v[i];
//        if(p==pre)
//            continue;
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
void add(int x,int y)
{
    v[++num]=y;
    ext[num]=first[x];
    first[x]=num;
}
int main()
{
    memset(col,0,sizeof(col));
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(vis,false,sizeof(vis));
    memset(first,-1,sizeof(first));
    num=cnt=tot=0;
    scanf("%d",&n);
    for(int i=1; i<=n; ++i)
    {
        int num;
        scanf("%d",&num);
        while(num--)
        {
            int y;
            scanf("%d",&y);
            add(i,y+n);
        }
    }
    for(int i=1; i<=n; ++i)
    {
        int y;
        scanf("%d",&y);
        add(y+n,i);
    }
    for(int i=1; i<=2*n; ++i)
        if(!dfn[i])
            tarjan(i,i);
    for(int i=1; i<=n; ++i)
    {
        int k=col[i],cnt=0;
        for(int j=first[i]; ~j; j=ext[j])
        {
            int p=v[j];
            if(col[p]==col[i])
                ans[++cnt]=p;
        }
        sort(ans+1,ans+1+cnt);
        printf("%d ",cnt);
        for(int j=1; j<=cnt; ++j)
            printf("%d ",ans[j]-n);
        printf("\n");
    }
}
//poj1904