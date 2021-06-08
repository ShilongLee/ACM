#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
const int N=100005;
int n,m,st,mod;
int v[N<<1],first[N<<1],ext[N<<1],cnt;
int rt[N],depth[N],siz[N],hson[N];
int tim,dfn[N],top[N],w[N],a[N];
struct node
{
    int l,r;
    int sum,add;
} tree[N<<2];
void add(int x,int y)
{
    v[++cnt]=y;
    ext[cnt]=first[x];
    first[x]=cnt;
}
void push_down(int root)
{
    tree[root<<1].add+=tree[root].add;
    tree[root<<1|1].add+=tree[root].add;
    tree[root<<1].sum+=tree[root].add*(tree[root<<1].r-tree[root<<1].l+1);
    tree[root<<1|1].sum+=tree[root].add*(tree[root<<1|1].r-tree[root<<1|1].l+1);
    tree[root].add=0;
    tree[root<<1].add%=mod;
    tree[root<<1|1].add%=mod;
    tree[root<<1].sum%=mod;
    tree[root<<1|1].sum%=mod;
}
void build(int l,int r,int root)
{
    tree[root].l=l;
    tree[root].r=r;
    tree[root].add=0;
    if(l==r)
    {
        tree[root].sum=w[l];
        return;
    }
    int mid=(tree[root].l+tree[root].r)>>1;
    build(l,mid,root<<1);
    build(mid+1,r,root<<1|1);
    tree[root].sum=(tree[root<<1].sum+tree[root<<1|1].sum)%mod;
}
void update(int l,int r,int z,int root)
{
    if(l>tree[root].r||r<tree[root].l)
        return;
    if(tree[root].l==l&&tree[root].r==r)
    {
        tree[root].sum=(tree[root].sum+(tree[root].r-tree[root].l+1)*z%mod)%mod;
        tree[root].add=(tree[root].add+z)%mod;
        return;
    }
    if(tree[root].add>0)
        push_down(root);
    int mid=(tree[root].l+tree[root].r)>>1;
    if(r<=mid)
        update(l,r,z,root<<1);
    else if(l>mid)
        update(l,r,z,root<<1|1);
    else
        update(l,mid,z,root<<1),update(mid+1,r,z,root<<1|1);
    tree[root].sum=(tree[root<<1].sum+tree[root<<1|1].sum)%mod;
}
int query(int l,int r,int root)
{
    if(l>tree[root].r||r<tree[root].l)
        return 0;
    if(tree[root].l==l&&tree[root].r==r)
        return tree[root].sum;
    if(tree[root].add>0)
        push_down(root);
    int mid=(tree[root].l+tree[root].r)>>1;
    if(r<=mid)
        return query(l,r,root<<1);
    else if(l>mid)
        return query(l,r,root<<1|1);
    else
        return (query(l,mid,root<<1)+query(mid+1,r,root<<1|1))%mod;
}
void ud_chain(int x,int y,int z)
{
    z%=mod;
    while(top[x]!=top[y])
    {
        if(depth[top[x]]<depth[top[y]])
            swap(x,y);
        update(dfn[top[x]],dfn[x],z,1);
        x=rt[top[x]];
    }
    if(depth[x]>depth[y])
        swap(x,y);
    update(dfn[x],dfn[y],z,1);
}
int query_chain(int x,int y)
{
    int ans=0;
    while(top[x]!=top[y])
    {
        if(depth[top[x]]<depth[top[y]])
            swap(x,y);
        ans+=query(dfn[top[x]],dfn[x],1);
        x=rt[top[x]];
    }
    if(depth[x]>depth[y])
        swap(x,y);
    ans+=query(dfn[x],dfn[y],1);
    return ans%mod;
}
void dfs2(int st,int t)
{
    dfn[st]=++tim;
    top[st]=t;
    w[tim]=a[st];
    if(!hson[st])
        return;
    dfs2(hson[st],t);
    for(int i=first[st]; i!=-1; i=ext[i])
    {
        int p=v[i];
        if(p==rt[st]||p==hson[st])
            continue;
        dfs2(p,p);
    }
}
void dfs1(int st,int pre)
{
    rt[st]=pre;
    depth[st]=depth[pre]+1;
    siz[st]=1;
    int maxsize=-1;
    for(int i=first[st]; i!=-1; i=ext[i])
    {
        int p=v[i];
        if(p==pre)
            continue;
        dfs1(p,st);
        siz[st]+=siz[p];
        if(siz[p]>maxsize)
        {
            maxsize=siz[p];
            hson[st]=p;
        }
    }
}
int main()
{
    cnt=0,tim=0;
    memset(depth,0,sizeof(depth));
    memset(first,-1,sizeof(first));
    cin>>n>>m>>st>>mod;
    for(int i=1; i<=n; ++i)
        cin>>a[i];
    for(int i=1; i<=n-1; ++i)
    {
        int x,y;
        cin>>x>>y;
        add(x,y);
        add(y,x);
    }
    dfs1(st,st);
    dfs2(st,st);
    build(1,n,1);
    while(m--)
    {
        int op,x,y,z;
        cin>>op;
        if(op==1)
        {
            cin>>x>>y>>z;
            ud_chain(x,y,z%mod);
        }
        else if(op==2)
        {
            cin>>x>>y;
            cout<<query_chain(x,y)<<endl;
        }
        else if(op==3)
        {
            cin>>x>>z;
            update(dfn[x],dfn[x]+siz[x]-1,z%mod,1);
        }
        else
        {
            cin>>x;
            cout<<query(dfn[x],dfn[x]+siz[x]-1,1)<<endl;
        }
    }
}
//洛谷3384树链剖分
//解题步骤：
//1：先存图；
//2：dfs1出每个节点的父节点，深度，重儿子和节点的size；
//3：dfs2出每个结点的dfs序，每个节点的新编号，和新编号对应的权重，还有每个节点的重链的头部。
//4：每次进行两个点的更改时，把（重链的头部）深度比较深的节点往上跳，每次跳到一条重链上，直到同一条重链，不在同一条重链时，更新x到重链头部的区间（重链区间是连续的，线段树更新），再一条重链时直接更新重链两点之间的区间。
