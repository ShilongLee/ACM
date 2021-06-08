#include<iostream>
#include<string.h>
using namespace std;
int rt[1005];
int vis[1005];
int sum;
int fin(int x)
{
    if(rt[x]==x)
        return x;
    return rt[x]=fin(rt[x]);
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        sum=0;
        memset(vis,0,sizeof(vis));
        memset(rt,0,sizeof(rt));
        int n,m;
        cin>>n>>m;
        for(int i=1; i<=n; ++i)
            rt[i]=i;
        while(m--)
        {
            int x,y,xx,yy;
            cin>>x>>y;
            xx=fin(x);
            yy=fin(y);
            if(xx!=yy)
                rt[xx]=yy;
        }
        /*int q;
        cin>>q;
        while(q--)
        {
            int x,y;
            cin>>x>>y;
            if(fin(x)==fin(y))
                cout<<"Yes"<<endl;
            else cout<<"No"<<endl;
        }*/
        for(int i=1; i<=n; ++i)
        {
            if(!vis[fin(i)])
            {
                sum++;
                vis[fin(i)]=1;
            }
        }
        cout<<sum<<endl;
    }
}
//hdu 1213