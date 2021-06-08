#include<stdio.h>
#include<algorithm>
#include<vector>
#include<string.h>
using namespace std;
const int N=1010;
const int inf=0x3f3f3f3f;
int n;
vector<double>v;
struct edge
{
    double x,y1,y2;
    int c;
    bool operator<(const edge &a)const
    {
        return x<a.x;
    }
} e[N<<2];
struct node
{
    int l,r,lazy;
    double len1,len2;
} tree[N<<4];
int fin(double x)
{
    return lower_bound(v.begin(),v.end(),x)-v.begin();
}
void push_up(int root)
{
    if(tree[root].lazy>0)
        tree[root].len1=v[tree[root].r+1]-v[tree[root].l];
    else if(tree[root].l!=tree[root].r)
        tree[root].len1=tree[root<<1].len1+tree[root<<1|1].len1;
    else
        tree[root].len1=0;
    if(tree[root].lazy>1)
        tree[root].len2=v[tree[root].r+1]-v[tree[root].l];
    else if(tree[root].lazy>0)
        tree[root].len2=tree[root<<1].len1+tree[root<<1|1].len1;
    else if(tree[root].l!=tree[root].r)
        tree[root].len2=tree[root<<1].len2+tree[root<<1|1].len2;
    else
        tree[root].len2=0;
}
void build(int l,int r,int root)
{
    tree[root]= {l,r,0,0,0};
    if(l==r)
        return;
    int mid=(l+r)>>1;
    build(l,mid,root<<1);
    build(mid+1,r,root<<1|1);
}
void update(int l,int r,int c,int root)
{
    if(l>tree[root].r||r<tree[root].l)
        return;
    if(tree[root].l==l&&tree[root].r==r)
    {
        tree[root].lazy+=c;
        push_up(root);
        return;
    }
    int mid=(tree[root].l+tree[root].r)>>1;
    if(r<=mid)
        update(l,r,c,root<<1);
    else if(l>mid)
        update(l,r,c,root<<1|1);
    else
        update(l,mid,c,root<<1),update(mid+1,r,c,root<<1|1);
    push_up(root);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        v.clear();
        v.push_back(-inf);
        double x1,y1,x2,y2;
        int cnt=0;
        for(int i=1; i<=n; ++i)
        {
            scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
            v.push_back(y1);
            v.push_back(y2);
            e[++cnt].x=x1;
            e[cnt].y1=y1;
            e[cnt].y2=y2;
            e[cnt].c=1;
            e[++cnt].x=x2;
            e[cnt].y1=y1;
            e[cnt].y2=y2;
            e[cnt].c=-1;
        }
        sort(v.begin(),v.end());
        v.erase(unique(v.begin(),v.end()),v.end());
        build(1,v.size()-2,1);
        sort(e+1,e+cnt+1);
        double ans=0,last=0;
        for(int i=1; i<=cnt; ++i)
        {
            ans+=(e[i].x-last)*tree[1].len2;
            last=e[i].x;
            update(fin(e[i].y1),fin(e[i].y2)-1,e[i].c,1);
        }
        printf("%.2lf\n",ans);
    }
}
//hdu1225