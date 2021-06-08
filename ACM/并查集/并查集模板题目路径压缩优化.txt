#include<iostream>
#include<string.h>
using namespace std;
int n,d;
int rt[1005];
int vis[1005];
int fin(int x)
{
    if(rt[x]==x)
        return x;
    return rt[x]=fin(rt[x]);
}
int dis(int x1,int y1,int x2,int y2)
{
    return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}
int posx[1005];
int posy[1005];
int main()
{
    memset(vis,0,sizeof(vis));
    memset(rt,0,sizeof(rt));
    cin>>n>>d;
    d=d*d;
    for(int i=1; i<=n; ++i)
        rt[i]=i;
    for(int i=1; i<=n; ++i)
        cin>>posx[i]>>posy[i];
    char c;
    while(cin>>c)
    {
        if(c=='O')
        {
            int x;
            cin>>x;
            vis[x]=1;
            for(int i=1;i<=n;++i)
            {
                if(i==x) continue;
                if(vis[i]&&dis(posx[x],posy[x],posx[i],posy[i])<=d)
                {
                    int xx=fin(x);
                    int yy=fin(i);
                    if(xx!=yy)
                        rt[xx]=yy;
                }
            }
        }
        else if(c=='S')
        {
            int x,y;
            cin>>x>>y;
            if(fin(x)==fin(y))
                cout<<"SUCCESS"<<endl;
            else cout<<"FAIL"<<endl;
        }
    }
}
//poj2236