#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
const int N=100005;
int v[N],first[N],ext[N],num;
int in[N],out[N],time;
int n,m;
struct node
{
    int l,r,sum,lazy;
} tree[N<<2];
void init()
{
    memset(first,-1,sizeof(first));
    num=0;
    time=0;
}
void add(int x,int y)
{
    v[++num]=y;
    ext[num]=first[x];
    first[x]=num;
}
void dfs(int x)
{
    in[x]=++time;
    for(int i=first[x]; i!=-1; i=ext[i])
        dfs(v[i]);
    out[x]=time;
}
void push_up(int root)
{
    tree[root].sum=tree[root<<1].sum+tree[root<<1|1].sum;
}
void build(int l,int r,int root)
{
    tree[root].l=l;
    tree[root].r=r;
    tree[root].lazy=0;
    if(l==r)
    {
        tree[root].sum=1;
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,root<<1);
    build(mid+1,r,root<<1|1);
    push_up(root);
}
void update(int l,int root)
{
    if(l>tree[root].r)
        return;
    if(tree[root].l==l&&tree[root].r==l)
    {
        if(tree[root].lazy==1)
        {
            tree[root].sum+=1;
            tree[root].lazy=0;
        }
        else if(tree[root].lazy==0)
        {
            tree[root].lazy=1;
            tree[root].sum-=1;
        }
        return;
    }
    int mid=(tree[root].l+tree[root].r)>>1;
    if(l<=mid) update(l,root<<1);
    else update(l,root<<1|1);
    push_up(root);
}
int query(int l,int r,int root)
{
    if(l>tree[root].r||r<tree[root].l)
        return 0;
    if(tree[root].l==l&&tree[root].r==r)
        return tree[root].sum;
    int mid=(tree[root].l+tree[root].r)>>1;
    if(r<=mid)
        return query(l,r,root<<1);
    else if(l>mid)
        return query(l,r,root<<1|1);
    else
        return query(l,mid,root<<1)+query(mid+1,r,root<<1|1);
}
int main()
{
    init();
    cin>>n;
    for(int i=1; i<=n-1; ++i)
    {
        int x,y;
        cin>>x>>y;
        add(x,y);
    }
    build(1,n,1);
    dfs(1);
//    for(int i=1;i<=n-1;++i)
//        cout<<v[i]<<' '<<first[i]<<' '<<ext[i]<<endl;
//    for(int i=1;i<=n;++i)
//        cout<<in[i]<<' '<<out[i]<<endl;
    cin>>m;
    while(m--)
    {
        char c;
        int x;
        cin>>c>>x;
        if(c=='C')
            update(in[x],1);
        else
            cout<<query(in[x],out[x],1)<<endl;
    }
}
//poj3321