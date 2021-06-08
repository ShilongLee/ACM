#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
const int N=50005;
int n,m,vis[N];
int v[N],first[N],ext[N],num;
int in[N],out[N],time;
struct node
{
    int l,r;
    int lazy,task;
} tree[N<<2];
void init()
{
    num=0;
    time=0;
    memset(vis,0,sizeof(vis));
    memset(first,-1,sizeof(first));
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
void push_down(int root)
{
    tree[root<<1].task=tree[root].lazy;
    tree[root<<1|1].task=tree[root].lazy;
    tree[root<<1].lazy=tree[root].lazy;
    tree[root<<1|1].lazy=tree[root].lazy;
    tree[root].lazy=-1;
}
void build(int l,int r,int root)
{
    tree[root]= {l,r,-1,-1};
    if(l==r)
        return;
    int mid=(l+r)>>1;
    build(l,mid,root<<1);
    build(mid+1,r,root<<1|1);
}
void update(int l,int r,int x,int root)
{
    if(r<tree[root].l||l>tree[root].r)
        return;
    if(tree[root].l==l&&tree[root].r==r)
    {
        tree[root].task=x;
        tree[root].lazy=x;
        return;
    }
    if(tree[root].lazy!=-1)
        push_down(root);
    int mid=(tree[root].l+tree[root].r)>>1;
    if(r<=mid)
        update(l,r,x,root<<1);
    else if(l>mid)
        update(l,r,x,root<<1|1);
    else
        update(l,mid,x,root<<1),update(mid+1,r,x,root<<1|1);
}
int query(int l,int r,int root)
{
    if(r<tree[root].l||l>tree[root].r)
        return 0;
    if(tree[root].l==l&&tree[root].r==r)
        return tree[root].task;
    if(tree[root].lazy!=-1)
        push_down(root);
    int mid=(tree[root].l+tree[root].r)>>1;
    if(r<=mid)
        return query(l,r,root<<1);
    else if(l>mid)
        return query(l,r,root<<1|1);
    else
        return query(l,mid,root<<1);
}
int main()
{
    int t;
    cin>>t;
    int cnt=0;
    while(t--)
    {
        cout<<"Case #"<<++cnt<<":"<<endl;
        init();
        cin>>n;
        for(int i=1; i<=n-1; ++i)
        {
            int x,y;
            cin>>x>>y;
            add(y,x);
            vis[x]=1;
        }
        for(int i=1; i<=n; ++i)
            if(!vis[i])
                dfs(i);
        build(1,n,1);
        cin>>m;
        while(m--)
        {
            int x,y;
            char c;
            cin>>c;
            if(c=='C')
            {
                cin>>x;
                cout<<query(in[x],out[x],1)<<endl;
            }
            else
            {
                cin>>x>>y;
                update(in[x],out[x],y,1);
            }
        }
    }
}
//hdu3974
