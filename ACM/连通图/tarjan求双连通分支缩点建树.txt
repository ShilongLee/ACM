#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<stack>
#include<string.h>
using namespace std;
const int N=310005;
const int M=5000005;
int n,m,q,v[M],first[M],ext[M],num,dfn[N],low[N],cnt;
int v2[M],first2[M],ext2[M],num2,rt[N],depth[N],all,father[N],col[N];
bool vis[N];
stack<int>s;
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
void tarjan(int st,int pre)
{
    dfn[st]=low[st]=++cnt;
    vis[st]=true;
    s.push(st);
    //int pre_cnt=0;
    for(int i=first[st]; ~i; i=ext[i])
    {
        int p=v[i];
        if(p==pre)
        {

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
        ++all;
        while(s.top()!=st)
        {
            int k=s.top();
            col[k]=all;
            vis[k]=false;
            s.pop();
        }
        int k=s.top();
        col[k]=all;
        vis[k]=false;
        s.pop();
    }
}
void dfs(int st,int pre,int d)
{
    rt[st]=pre;
    depth[st]=d;
    for(int i=first2[st]; ~i; i=ext2[i])
    {
        int p=v2[i];
        if(p==pre)
            continue;
        dfs(p,st,d+1);
    }
}
int fin(int x)
{
    if(father[x]==x)
        return x;
    return father[x]=fin(father[x]);
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
        {
            x=rt[x];
            y=rt[y];
        }
        x=fin(x);
        y=fin(y);
    }
    return x;
}
int main()
{
    int c=0;
    while(cin>>n>>m)
    {
        if(n==0&&m==0)
            break;
        memset(vis,false,sizeof(vis));
        memset(dfn,0,sizeof(dfn));
        memset(col,0,sizeof(col));
        memset(depth,0,sizeof(depth));
        memset(low,0,sizeof(low));
        memset(first2,-1,sizeof(first2));
        memset(first,-1,sizeof(first));
        num=0,cnt=0,num2=0,all=0;
        for(int i=1; i<=n; ++i)
            rt[i]=i;
        for(int i=1; i<=n; ++i)
            father[i]=i;
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
//        int k=1;
//        for(int i=1; i<=n; ++i)
//            for(int j=first[i]; ~j; j=ext[j])
//            {
//                int p=v[j];
//                if(low[i]!=low[p])
//                {
//                    //vis[low[i]]=vis[low[p]]=true;
//                    k=low[i];
//                    add2(low[i],low[p]);
//                    all++;
//                }
//            }
        all=0;
        for(int i=1; i<=n; ++i)
        {
            for(int j=first[i]; ~j; j=ext[j])
            {
                int p=v[j];
                if(col[i]!=col[p])
                    all++,add2(col[i],col[p]);
            }
        }
        all/=2;
        dfs(1,1,1);
        //dfs(k,1,1);
        cin>>q;
        printf("Case %d:\n", ++c);
        while(q--)
        {
            int a,b,lca,sum=0;
            cin>>a>>b;
            int x=col[a],y=col[b];
            if(x==y/*||!vis[x]||!vis[y]*/)
            {
                cout<<all<<endl;
                continue;
            }
            x=fin(x);
            y=fin(y);
            lca=LCA(x,y);
            while(x!=lca)
            {
                ++sum;
                father[x]=lca;
                x=rt[x];
                x=fin(x);
            }
            while(y!=lca)
            {
                ++sum;
                father[y]=lca;
                y=rt[y];
                y=fin(y);
            }
            all-=sum;
            cout<<all<<endl;
        }
        cout<<endl;
    }
    return 0;
}
//poj3694