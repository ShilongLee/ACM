#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
const int N=10005;
int ans;
bool vis[N<<3];
int l[N<<1];
int r[N<<1];
int a[N<<2];
int n;
struct node
{
    int l,r,lazy;
} tree[N<<4];
void build(int l,int r,int root)
{
    tree[root].l=l;
    tree[root].r=r;
    tree[root].lazy=-1;
    if(l==r)
        return;
    int mid=(l+r)>>1;
    build(l,mid,root<<1);
    build(mid+1,r,root<<1|1);
}
void push_down(int root)
{
    tree[root<<1].lazy=tree[root].lazy;
    tree[root<<1|1].lazy=tree[root].lazy;
    tree[root].lazy=-1;
}
void update(int l,int r,int c,int root)
{
    if(l==tree[root].l&&r==tree[root].r)
    {
        tree[root].lazy=c;
        return;
    }
    if(tree[root].lazy!=-1)
        push_down(root);
    int mid=(tree[root].l+tree[root].r)>>1;
    if(r<=mid)
        update(l,r,c,root<<1);
    else if(l>mid)
        update(l,r,c,root<<1|1);
    else
        update(l,mid,c,root<<1),update(mid+1,r,c,root<<1|1);
}
void query(int l,int r,int root)
{
    if(tree[root].lazy!=-1&&!vis[tree[root].lazy])
    {
        ans++;
        vis[tree[root].lazy]=true;
        return;
    }
    if(l==r||tree[root].lazy!=-1)
        return;
    int mid=(tree[root].l+tree[root].r)>>1;
    if(r<=mid)
        query(l,r,root<<1);
    else if(l>mid)
        query(l,r,root<<1|1);
    else
        query(l,mid,root<<1),query(mid+1,r,root<<1|1);
}
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int t;
    cin>>t;
    while(t--)
    {
        ans=0;
        memset(vis,false,sizeof(vis));
        cin>>n;
        int num=0;
        for(int i=1; i<=n; ++i)
        {
            cin>>l[i]>>r[i];
            a[++num]=l[i];
            a[++num]=r[i];
        }
        int sum=num>>1;
        sort(a+1,a+num+1);
        num=unique(a+1,a+num+1)-&a[1];
        int pos=num;
        for(int i=1; i<=num; ++i)
            if(a[i]-a[i-1]>1)
                a[++pos]=a[i-1]+1;
        num=pos;
        sort(a+1,a+1+num);
        build(1,num,1);
//        for(int i=1;i<=num;++i)
//            cout<<a[i]<<' ';
//        cout<<endl;
        for(int i=1; i<=sum; ++i)
        {
            int x=lower_bound(a+1,a+num+1,l[i])-a;
            int y=lower_bound(a+1,a+num+1,r[i])-a;
            update(x,y,i,1);
        }
        query(1,num,1);
        cout<<ans<<endl;
    }
    return 0;
}
//poj2528
