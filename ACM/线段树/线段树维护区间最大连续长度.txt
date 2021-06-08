#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<string>
using namespace std;
const int T=100010;
int t,n;
struct node
{
    int l,r;
    int fmax[2],lmax[2],rmax[2];
    int lazy[2];
} tree[T<<4];
void push_up(int root,int id)
{
    node &p=tree[root],&l=tree[root<<1],&r=tree[root<<1|1];
    p.fmax[id]=max(max(l.fmax[id],r.fmax[id]),l.rmax[id]+r.lmax[id]);
    p.lmax[id]=l.lmax[id]+((l.lmax[id]==(l.r-l.l+1))? r.lmax[id] : 0);
    p.rmax[id]=r.rmax[id]+((r.rmax[id]==(r.r-r.l+1))? l.rmax[id] : 0);
}
void push_down(int root,int id)
{
    tree[root<<1].fmax[id]=tree[root<<1].lmax[id]=tree[root<<1].rmax[id]=(tree[root<<1].r-tree[root<<1].l+1)*tree[root].lazy[id];
    tree[root<<1|1].fmax[id]=tree[root<<1|1].lmax[id]=tree[root<<1|1].rmax[id]=(tree[root<<1|1].r-tree[root<<1|1].l+1)*tree[root].lazy[id];
    tree[root<<1].lazy[id]=tree[root<<1|1].lazy[id]=tree[root].lazy[id];
    tree[root].lazy[id]=-1;
}
void build(int l,int r,int root)
{
    tree[root].l=l;
    tree[root].r=r;
    tree[root].lazy[0]=tree[root].lazy[1]=-1;
    if(l==r)
    {
        tree[root].fmax[0]=tree[root].fmax[1]=1;
        tree[root].lmax[0]=tree[root].lmax[1]=1;
        tree[root].rmax[0]=tree[root].rmax[1]=1;
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,root<<1);
    build(mid+1,r,root<<1|1);
    push_up(root,0);
    push_up(root,1);
}
void update(int l,int r,int id,int c,int root)
{
    if(tree[root].l==l&&tree[root].r==r)
    {
        tree[root].fmax[id]=tree[root].lmax[id]=tree[root].rmax[id]=(tree[root].r-tree[root].l+1)*c;
        tree[root].lazy[id]=c;
        return;
    }
    if(tree[root].lazy[id]!=-1)
        push_down(root,id);
    int mid=(tree[root].l+tree[root].r)>>1;
    if(r<=mid)
        update(l,r,id,c,root<<1);
    else if(l>mid)
        update(l,r,id,c,root<<1|1);
    else
        update(l,mid,id,c,root<<1),update(mid+1,r,id,c,root<<1|1);
    push_up(root,id);
}
int find_left(int id,int c,int root)
{
    if(tree[root].l==tree[root].r)
        return tree[root].l;
    if(tree[root].lazy[id]!=-1)
        push_down(root,id);
    if(tree[root<<1].fmax[id]>=c)
        return find_left(id,c,root<<1);
    if(tree[root<<1].rmax[id]+tree[root<<1|1].lmax[id]>=c)
        return tree[root<<1].r-tree[root<<1].rmax[id]+1;
    return find_left(id,c,root<<1|1);
}
int main()
{
    int cas,cnt=0;
    scanf("%d",&cas);
    while(cas--)
    {
        printf("Case %d:\n", ++cnt);
        scanf("%d%d",&t,&n);
        build(1,t,1);
        int l,r,c,id;
        char s[10];
        for(int i=1; i<=n; ++i)
        {
            scanf("%s",s);
            if(*s=='S')
            {
                scanf("%d%d",&l,&r);
                update(l,r,0,1,1);
                update(l,r,1,1,1);
                printf("I am the hope of chinese chengxuyuan!!\n");
            }
            else if(*s=='N')
            {
                id=-1;
                scanf("%d",&c);
                if(tree[1].fmax[0]>=c)
                    id=0;
                else if(tree[1].fmax[1]>=c)
                    id=1;
                if(id==-1)
                {
                    printf("wait for me\n");
                    continue;
                }
                l=find_left(id,c,1);
                printf("%d,don't put my gezi\n", l);
                update(l,l+c-1,0,0,1);
                update(l,l+c-1,1,0,1);
            }
            else if(*s=='D')
            {
                id=-1;
                scanf("%d",&c);
                if(tree[1].fmax[0]>=c)
                    id=0;
                if(id==-1)
                {
                    printf("fly with yourself\n");
                    continue;
                }
                l=find_left(0,c,1);
                printf("%d,let's fly\n", l);
                update(l,l+c-1,0,0,1);
            }
        }
    }
}
//hdu4553