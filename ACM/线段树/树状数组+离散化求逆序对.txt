#include<iostream>
#include<string.h>
#include<map>
#include<algorithm>
using namespace std;
const int N=105;
int n;
int b[N];
int tree[N];
struct node
{
    int val,pos;
} a[N];
void update(int x)
{
    for(int i=x;i<=n;i+=i&(-i))
        tree[i]++;
}
int query(int x)
{
    int sum=0;
    for(int i=x;i>=1;i-=i&(-i))
        sum+=tree[i];
    return sum;
}
bool cmp(node a,node b)
{
    return a.val<b.val;
}
int main()
{
    while(cin>>n)
    {
        memset(tree,0,sizeof(tree));
        memset(b,0,sizeof(b));
        for(int i=1; i<=n; ++i)
        {
            cin>>a[i].val;
            a[i].pos=i;
        }
        sort(a+1,a+n+1,cmp);
        int cnt=1;
        for(int i=1;i<=n;++i)
        {
            if(i!=1&&a[i].val!=a[i-1].val)
                cnt++;
            b[a[i].pos]=cnt;
        }
        for(int i=1;i<=n;++i)
            cout<<b[i]<<' ';
        cout<<endl;
        int sum=0;
        for(int i=1;i<=n;++i)
        {
            update(b[i]);
            sum+=i-query(b[i]);
        }
        cout<<sum<<endl;
    }
}
//树状数组求逆序对
//https://blog.csdn.net/bestsort/article/details/80796531