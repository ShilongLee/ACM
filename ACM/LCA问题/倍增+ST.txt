#include<iostream>
#include<algorithm>
#include<string.h>
#include<math.h>
using namespace std;
const int N=500005;
const int M=500005;
int n,m,st,maxd;
int v[N<<1],first[N<<1],ext[N<<1],num;
int depth[N];
int rt[N][50];
void add(int x,int y)
{
    v[++num]=y;
    ext[num]=first[x];
    first[x]=num;
}
void dfs(int pre,int st)
{
    depth[st]=depth[pre]+1;
    rt[st][0]=pre;
    for(int i=1; (1<<i)<=n; ++i)
        rt[st][i]=rt[rt[st][i-1]][i-1];
    for(int i=first[st]; i!=-1; i=ext[i])
    {
        int p=v[i];
        if(p!=pre)
            dfs(st,p);
    }
}
int up(int x,int d)
{
    int res=x;
    for(int i=0; (1<<i)<=n; ++i)
        if((1<<i)&d)
            res=rt[res][i];
    return res;
}
int lca(int x,int y)
{
    if(depth[x]>depth[y])
        swap(x,y);
    y=up(y,depth[y]-depth[x]);
    if(x==y) return x;
    for(int i=maxd;i>=0;--i)
        if(rt[x][i]!=rt[y][i])
        x=rt[x][i],y=rt[y][i];
    return rt[x][0];
}
int main()
{
    cin>>n>>m>>st;
    num=0;
    maxd=log(n)/log(2);
    memset(depth,0,sizeof(depth));
    memset(first,-1,sizeof(first));
    for(int i=1; i<=n-1; ++i)
    {
        int x,y;
        cin>>x>>y;
        add(x,y);
        add(y,x);
    }
    dfs(st,st);
    while(m--)
    {
        int x,y;
        cin>>x>>y;
        cout<<lca(x,y)<<endl;
    }
}
//洛谷3379
//三步走
//第一步 dfs出ST表（每个节点的第2^i个祖先）
//第二步 写up函数任意一个点上移step步所到达的点（二进制分解）
//第三步 把两点上升到同一位置，然后从同时上跳，祖先不同时上跳