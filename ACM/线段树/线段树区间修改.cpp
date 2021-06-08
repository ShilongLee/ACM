#include<iostream>
#include<string.h>
#include<string>
#include<algorithm>
using namespace std;
const int N=100005;
int a[N];
struct node
{
    int l,r;
    long long sum;
    long long add;
} tree[4*N];
void build(int l,int r,int root)
{
    tree[root].l=l;
    tree[root].r=r;
    tree[root].add=0;
    if(l==r)
    {
        tree[root].sum=a[l];
        return;
    }
    int mid=(l+r)/2;
    build(l,mid,root*2);
    build(mid+1,r,root*2+1);
    tree[root].sum=tree[root*2].sum+tree[root*2+1].sum;
}
void push_down(int root)
{
    tree[root*2].sum+=tree[root].add*(tree[root*2].r-tree[root*2].l+1);
    tree[root*2+1].sum+=tree[root].add*(tree[root*2+1].r-tree[root*2+1].l+1);
    tree[root*2].add+=tree[root].add;
    tree[root*2+1].add+=tree[root].add;
    tree[root].add=0;
}
void update(int l,int r,int x,int root)
{
    if(tree[root].l==l&&tree[root].r==r)
    {
        tree[root].sum+=(tree[root].r-tree[root].l+1)*x;
        tree[root].add+=x;
        return ;
    }
    if(tree[root].add)
        push_down(root);
    int mid=(tree[root].l+tree[root].r)/2;
    if(r<=mid)
        update(l,r,x,root*2);
    else if(l>mid)
        update(l,r,x,root*2+1);
    else
    {
        update(l,mid,x,root*2);
        update(mid+1,r,x,root*2+1);
    }
    tree[root].sum=tree[root*2].sum+tree[root*2+1].sum;
}
long long query(int l,int r,int root)
{
    if(tree[root].l==l&&tree[root].r==r)
        return tree[root].sum;
    if(tree[root].add)
        push_down(root);
    int mid=(tree[root].l+tree[root].r)/2;
    if(r<=mid)
        return query(l,r,root*2);
    else if(l>mid)
        return query(l,r,root*2+1);
    else
        return query(l,mid,root*2)+query(mid+1,r,root*2+1);
}
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1; i<=n; ++i)
        cin>>a[i];
    build(1,n,1);
    while(m--)
    {
        string s;
        int a,b,c;
        cin>>s;
        if(s=="C")
        {
            cin>>a>>b>>c;
            update(a,b,c,1);
        }
        else if(s=="Q")
        {
            cin>>a>>b;
            cout<<query(a,b,1)<<endl;
        }
    }
}
//poj3468
//用stdio会更快