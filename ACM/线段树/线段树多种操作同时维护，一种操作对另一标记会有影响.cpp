#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
const int N=100005;
const int mod=10007;
int n,m;
struct node
{
    int l,r;
    int sum1,sum2,sum3;
    int add,mul,lazy;
} tree[N<<2];
void push_up(int root)
{
    tree[root].sum1=(tree[root<<1].sum1+tree[root<<1|1].sum1)%mod;
    tree[root].sum2=(tree[root<<1].sum2+tree[root<<1|1].sum2)%mod;
    tree[root].sum3=(tree[root<<1].sum3+tree[root<<1|1].sum3)%mod;
}
void push_down(int root)
{
    if(tree[root].lazy!=-1)
    {
        int c=tree[root].lazy;
        tree[root<<1].sum1=(tree[root<<1].r-tree[root<<1].l+1)*c%mod;
        tree[root<<1].sum2=(tree[root<<1].sum1*c)%mod;
        tree[root<<1].sum3=(tree[root<<1].sum2*c)%mod;
        tree[root<<1].lazy=c;
        tree[root<<1].mul=1;
        tree[root<<1].add=0;
        tree[root<<1|1].sum1=(tree[root<<1|1].r-tree[root<<1|1].l+1)*c%mod;
        tree[root<<1|1].sum2=(tree[root<<1|1].sum1*c)%mod;
        tree[root<<1|1].sum3=(tree[root<<1|1].sum2*c)%mod;
        tree[root<<1|1].lazy=c;
        tree[root<<1|1].mul=1;
        tree[root<<1|1].add=0;
        tree[root].lazy=-1;
    }
    if(tree[root].mul!=1)
    {
        int c=tree[root].mul;
        tree[root<<1].sum1=tree[root<<1].sum1*c%mod;
        tree[root<<1].sum2=(((tree[root<<1].sum2*c)%mod)*c)%mod;
        tree[root<<1].sum3=(((((tree[root<<1].sum3*c)%mod)*c)%mod)*c)%mod;
        tree[root<<1].mul=tree[root<<1].mul*c%mod;
        tree[root<<1].add=tree[root<<1].add*c%mod;
        tree[root<<1|1].sum1=tree[root<<1|1].sum1*c%mod;
        tree[root<<1|1].sum2=(((tree[root<<1|1].sum2*c)%mod)*c)%mod;
        tree[root<<1|1].sum3=(((((tree[root<<1|1].sum3*c)%mod)*c)%mod)*c)%mod;
        tree[root<<1|1].mul=tree[root<<1|1].mul*c%mod;
        tree[root<<1|1].add=tree[root<<1|1].add*c%mod;
        tree[root].mul=1;
    }
    if(tree[root].add!=0)
    {
        int c=tree[root].add;
        tree[root<<1].sum3=(tree[root<<1].sum3+(3*c%mod)*tree[root<<1].sum2%mod+((3*c%mod)*c%mod)*tree[root<<1].sum1%mod+(((tree[root<<1].r-tree[root<<1].l+1)*c%mod)*c%mod)*c%mod)%mod;
        tree[root<<1].sum2=(tree[root<<1].sum2+(2*(c*tree[root<<1].sum1%mod)%mod)+((tree[root<<1].r-tree[root<<1].l+1)*c%mod)*c%mod)%mod;
        tree[root<<1].sum1=(tree[root<<1].sum1+(tree[root<<1].r-tree[root<<1].l+1)*c%mod)%mod;
        tree[root<<1].add=(tree[root<<1].add+c)%mod;
        tree[root<<1|1].sum3=(tree[root<<1|1].sum3+(3*c%mod)*tree[root<<1|1].sum2%mod+((3*c%mod)*c%mod)*tree[root<<1|1].sum1%mod+(((tree[root<<1|1].r-tree[root<<1|1].l+1)*c%mod)*c%mod)*c%mod)%mod;
        tree[root<<1|1].sum2=(tree[root<<1|1].sum2+(2*(c*tree[root<<1|1].sum1%mod)%mod)+((tree[root<<1|1].r-tree[root<<1|1].l+1)*c%mod)*c%mod)%mod;
        tree[root<<1|1].sum1=(tree[root<<1|1].sum1+(tree[root<<1|1].r-tree[root<<1|1].l+1)*c%mod)%mod;
        tree[root<<1|1].add=(tree[root<<1|1].add+c)%mod;
        tree[root].add=0;
    }
}
void build(int l,int r,int root)
{
    tree[root]= {l,r,0,0,0,0,1,-1};
    if(l==r)
        return;
    int mid=(l+r)>>1;
    build(l,mid,root<<1);
    build(mid+1,r,root<<1|1);
}
void update(int l,int r,int op,int c,int root)
{
    if(r<tree[root].l||tree[root].r<l)
        return;
    if(tree[root].l==l&&tree[root].r==r)
    {
        if(op==1)
        {
            tree[root].sum3=(tree[root].sum3+(3*c%mod)*tree[root].sum2%mod+((3*c%mod)*c%mod)*tree[root].sum1%mod+(((tree[root].r-tree[root].l+1)*c%mod)*c%mod)*c%mod)%mod;
            tree[root].sum2=(tree[root].sum2+(2*(c*tree[root].sum1%mod)%mod)+((tree[root].r-tree[root].l+1)*c%mod)*c%mod)%mod;
            tree[root].sum1=(tree[root].sum1+(tree[root].r-tree[root].l+1)*c%mod)%mod;
            tree[root].add=(tree[root].add+c)%mod;
        }
        else if(op==2)
        {
            tree[root].sum1=tree[root].sum1*c%mod;
            tree[root].sum2=(((tree[root].sum2*c)%mod)*c)%mod;
            tree[root].sum3=(((((tree[root].sum3*c)%mod)*c)%mod)*c)%mod;
            tree[root].mul=tree[root].mul*c%mod;
            tree[root].add=tree[root].add*c%mod;
        }
        else
        {
            tree[root].sum1=(tree[root].r-tree[root].l+1)*c%mod;
            tree[root].sum2=(tree[root].sum1*c)%mod;
            tree[root].sum3=(tree[root].sum2*c)%mod;
            tree[root].lazy=c;
            tree[root].mul=1;
            tree[root].add=0;
        }
        return;
    }
    push_down(root);
    int mid=(tree[root].l+tree[root].r)>>1;
    if(r<=mid)
        update(l,r,op,c,root<<1);
    else if(l>mid)
        update(l,r,op,c,root<<1|1);
    else update(l,mid,op,c,root<<1),update(mid+1,r,op,c,root<<1|1);
    push_up(root);
}
int query(int l,int r,int c,int root)
{
    if(l>tree[root].r||tree[root].l>r) return 0;
    if(tree[root].l==l&&tree[root].r==r)
    {
        if(c==1) return tree[root].sum1;
        else if(c==2) return tree[root].sum2;
        else return tree[root].sum3;
    }
    push_down(root);
    int mid=(tree[root].l+tree[root].r)>>1;
    if(r<=mid)
        return query(l,r,c,root<<1);
    else if(l>mid)
        return query(l,r,c,root<<1|1);
    else return (query(l,mid,c,root<<1)+query(mid+1,r,c,root<<1|1))%mod;
}
int main()
{
    while(cin>>n>>m&&n&&m)
    {
        build(1,n,1);
        int op,x,y,c;
        while(m--)
        {
            cin>>op>>x>>y>>c;
            if(op!=4)
                update(x,y,op,c,1);
            else
                cout<<query(x,y,c,1)<<endl;
        }
    }
}
//hdu4578