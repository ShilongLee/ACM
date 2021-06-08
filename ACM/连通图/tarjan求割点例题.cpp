#include<iostream>
#include<stdio.h>
#include<string.h>
#include<vector>
#include<algorithm>
using namespace std;
const int N=105;
const int M=N*N<<1;
int v[M],first[M],ext[M],num,n,m,dfn[N],low[N],cnt,sum;
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
    if(st==pre&&child>1)
        vis[st]=true;
}
int main()
{
    while(cin>>n&&n)
    {
        num=0,cnt=0,sum=0;
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        memset(first,-1,sizeof(first));
        memset(vis,false,sizeof(vis));
        int x,y;
        char c;
        while(cin>>x&&x)
        {
            while(~scanf("%d%c",&y,&c))
            {
                add(x,y);
                add(y,x);
                if(c=='\n')
                    break;
            }
        }
        for(int i=1; i<=n; ++i)
            if(!dfn[i])
                tarjan(i,i);
        for(int i=1; i<=n; ++i)
            if(vis[i])
                sum++;
        cout<<sum<<endl;
    }
}
//UVA-315
