#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
int n;
int a[105];
int tree[105];
void add(int x,int y)
{
    for(int i=x; i<=n; i+=i&-i)
        tree[i]+=y;
}
void rangeadd(int l,int r,int x)
{
    add(l,x);
    add(r+1,-x);
}
int query(int p)
{
    int res=0;
    for(int i=p; i>=1; i-=i&-i)
        res+=tree[i];
    return res;
}
int main()
{
    memset(a,0,sizeof(a));
    cin>>n;
    for(int i=1; i<=n; ++i)
        cin>>a[i];
    for(int i=n; i>=1; --i)
        a[i]=a[i]-a[i-1];
    for(int i=1; i<=n; ++i)
        add(i,a[i]);
    string s;
    while(cin>>s)
    {
        int l,r,x;
        if(s=="radd")
        {
            cin>>l>>r>>x;
            rangeadd(l,r,x);
        }
        else
        {
            cin>>x;
            cout<<query(x)<<endl;
        }
    }
}
//树状数组
//https://blog.csdn.net/bestsort/article/details/80796531