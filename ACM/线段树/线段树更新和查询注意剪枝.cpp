#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
const int N=100005;
int n,m;
long long  a[N];
struct node
{
    int l,r;
    long long sum;
} tree[N<<2];
void build(int l,int r,int root)
{
    tree[root].l=l;
    tree[root].r=r;
    if(l==r)
    {
        tree[root].sum=a[l];
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,root<<1);
    build(mid+1,r,root<<1|1);
    tree[root].sum=tree[root<<1].sum+tree[root<<1|1].sum;
}
void update(int l,int r,int root)
{
    if(l>tree[root].r||r<tree[root].l||tree[root].sum==(tree[root].r-tree[root].l+1))/////////////////////////
        return;
    if(tree[root].l==tree[root].r)
    {
        tree[root].sum=sqrt(tree[root].sum);
        return;
    }
    int mid=(tree[root].l+tree[root].r)>>1;
    if(r<=mid)
        update(l,r,root<<1);
    else if(l>mid)
        update(l,r,root<<1|1);
    else
        update(l,mid,root<<1),update(mid+1,r,root<<1|1);
    tree[root].sum=tree[root<<1].sum+tree[root<<1|1].sum;
}
long long query(int l,int r,int root)
{
    if(l>tree[root].r||r<tree[root].l)///////////////////////
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
    int cnt=0;
    while(~scanf("%d",&n)&&n!=-1)
    {
        memset(a,0,sizeof(a));
        for(int i=1; i<=n; ++i)
            scanf("%lld",&a[i]);
        build(1,n,1);
        scanf("%d",&m);
        int t,x,y;
        printf("Case #%d:\n",++cnt);
        while(m--)
        {
            scanf("%d%d%d",&t,&x,&y);
            if(t==0)
                update(min(x,y),max(x,y),1);
            else
                printf("%lld\n",query(min(x,y),max(x,y),1));
        }
        printf("\n");////////////////////
    }
}
//hdu4027
