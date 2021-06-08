#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
const int N=10005;
int n;
int l[N<<1];
int r[N<<1];
int a[N<<2];
int tree[N<<4];
bool vis[N<<3];
int ans=0;
void push_down(int root)
{
    tree[root<<1]=tree[root];
    tree[root<<1|1]=tree[root];
    tree[root]=-1;
}
void update(int l,int r,int L,int R,int x,int root)
{
    if(l==L&&r==R)
    {
        tree[root]=x;
        return;
    }
    if(tree[root]!=-1)
        push_down(root);
    int mid=(L+R)>>1;
    if(mid>=r)
        update(l,r,L,mid,x,root<<1);
    else if(mid<l)
        update(l,r,mid+1,R,x,root<<1|1);
    else update(l,mid,L,mid,x,root<<1),update(mid+1,r,mid+1,R,x,root<<1|1);
}
void query(int l,int r,int root)
{
    if(!vis[tree[root]]&&tree[root]!=-1)
    {
        vis[tree[root]]=true;
        ans++;
        return ;
    }
    if(l==r||tree[root]!=-1) return;
    int mid=(l+r)>>1;
    query(l,mid,root<<1);
    query(mid+1,r,root<<1|1);
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
        memset(tree,-1,sizeof(tree));
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
//        for(int i=1;i<=num;++i)
//            cout<<a[i]<<' ';
//        cout<<endl;
        int pos=num;
        for(int i=1; i<=num; ++i)
            if(a[i]-a[i-1]>1)
                a[++pos]=a[i-1]+1;
        num=pos;
        sort(a+1,a+num+1);
//        for(int i=1;i<=num;++i)
//            cout<<a[i]<<' ';
//        cout<<endl;
        for(int i=1; i<=sum; ++i)
        {
            int x=lower_bound(a+1,a+num+1,l[i])-a;
            int y=lower_bound(a+1,a+num+1,r[i])-a;
//            cout<<x<<' '<<y<<endl;
            update(x,y,1,num,i,1);
        }
        query(1,num,1);
        cout<<ans<<endl;
    }
}
//poj2528
