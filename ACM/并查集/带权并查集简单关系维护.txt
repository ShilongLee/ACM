#include<iostream>
#include<string.h>
using namespace std;
const int N=2005;
const int M=1000005;
int n,m;
int rt[N];
int dis[N];
int fin(int x)
{
    if(rt[x]==x)
        return x;
    int root=fin(rt[x]);
    dis[x]^=dis[rt[x]];
    return rt[x]=root;
}
int main()
{
    int t;
    cin>>t;
    for(int tt=1; tt<=t; tt++)
    {
        cin>>n>>m;
        memset(dis,0,sizeof(dis));
        for(int i=1; i<=n; ++i)
            rt[i]=i;
        int flag=0;
        while(m--)
        {
            int a,b;
            cin>>a>>b;
            int xx=fin(a);
            int yy=fin(b);
            if(xx!=yy)
            {
                rt[xx]=yy;
                dis[xx]=dis[a]^dis[b]^1;
            }
            else if(!(dis[a]^dis[b]))
                flag=1;
        }
        cout<<"Scenario #"<<tt<<":"<<endl;
        if(flag)
            cout<<"Suspicious bugs found!"<<endl;
        else
            cout<<"No suspicious bugs found!"<<endl;
            cout<<endl;
    }
}
//poj2492