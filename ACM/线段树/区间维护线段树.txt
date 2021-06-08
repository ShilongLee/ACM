#include<string.h>
#include<stdio.h>
#include<algorithm>
using namespace std;
typedef pair<int,int>pii;
const int N=50005;
int a[N];
struct node
{
    int l,r,Max,Min;
} tree[N<<2];
int n,q;
void build(int l,int r,int root)
{
    tree[root].l=l;
    tree[root].r=r;
    if(l==r)
    {
        tree[root].Max=tree[root].Min=a[l];
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,root<<1);
    build(mid+1,r,root<<1|1);
    tree[root].Max=max(tree[root<<1].Max,tree[root<<1|1].Max);
    tree[root].Min=min(tree[root<<1].Min,tree[root<<1|1].Min);
}
pii query(int l,int r,int root)
{
    if(tree[root].l==l&&tree[root].r==r)
        return pii(tree[root].Max,tree[root].Min);
    int mid=(tree[root].l+tree[root].r)>>1;
    if(r<=mid)
        return query(l,r,root<<1);
    else if(l>mid)
        return query(l,r,root<<1|1);
    else
    {
        pii p1=query(l,mid,root<<1);
        pii p2=query(mid+1,r,root<<1|1);
        return pii(max(p1.first,p2.first),min(p1.second,p2.second));
    }
}
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1; i<=n; ++i)
        scanf("%d",&a[i]);
    build(1,n,1);
    while(q--)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        pii p=query(l,r,1);
        printf("%d\n",p.first-p.second);
    }
}
//poj3264
