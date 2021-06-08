#include<iostream>
#include<string.h>
using namespace std;
const int N=200005;
int rt[N];
int dis[N];
int fin(int x)
{
    if(x==rt[x])
        return x;
    int root=fin(rt[x]);
    dis[x]+=dis[rt[x]];
    return rt[x]=root;
}
int main()
{
    int n,m;
    while(cin>>n>>m)
    {
        memset(dis,0,sizeof(dis));
        for(int i=0; i<=n; ++i)
            rt[i]=i;
        int sum=0;
        while(m--)
        {
            int a,b,s;
            cin>>a>>b>>s;
            --a;
            int xx=fin(a);
            int yy=fin(b);
            if(xx!=yy)
            {
                rt[xx]=yy;
                dis[xx]=dis[b]-dis[a]+s;
            }
            else
            {
                if(s!=dis[a]-dis[b])
                    sum++;
            }
        }
        cout<<sum<<endl;
    }
}
//带权并查集