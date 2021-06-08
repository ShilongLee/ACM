#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=50005;
int a[N];
int n;
int lowbit(int x)
{
    return x&(-x);
}
void update(int x,int y,int n)
{
    for(int i=x; i<=n; i+=lowbit(i))
        a[i]+=y;
}
int query(int b)
{
    int ans=0;
    for(int i=b; i>=1; i-=lowbit(i))
        ans+=a[i];
    return ans;
}
int main()
{
    int t;
    cin>>t;
    int cnt=0;
    while(t--)
    {
        memset(a,0,sizeof(a));
        cin>>n;
        int k;
        for(int i=1; i<=n; ++i)
        {
            cin>>k;
            update(i,k,n);
        }
        cout<<"Case "<<++cnt<<":"<<endl;
        char s[10];
        int x,y;
        while(1)
        {
            cin>>s;
            if(strcmp(s,"End")==0)
                break;
            cin>>x>>y;
            if(strcmp(s,"Add")==0)
                update(x,y,n);
            else if(strcmp(s,"Sub")==0)
                update(x,-y,n);
            else
                cout<<query(y)-query(x-1)<<endl;
        }
    }
}
//hdu1166
//https://blog.csdn.net/bestsort/article/details/80796531