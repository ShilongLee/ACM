#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
const int N=1005;
const int M=1005;
struct node
{
    int x;
    int y;
    int len;
}edge[M];
int rt[N];
bool cmp(node a,node b)
{
    return a.len<b.len;
}
int fin(int x)
{
    if(rt[x]==x)
        return x;
    return rt[x]=fin(rt[x]);
}
int main()
{
    int n,m,x,y,ans;
    cin>>n>>m;
    for(int i=1;i<=n;++i)
        rt[i]=i;
    for(int i=1;i<=m;++i)
        cin>>edge[i].x>>edge[i].y>>edge[i].len;
    sort(edge+1,edge+m+1,cmp);
    ans=0;
    for(int i=1;i<=m;++i)
    {
        int xx=fin(edge[i].x);
        int yy=fin(edge[i].y);
        if(xx!=yy)
        {
            rt[xx]=yy;
            ans+=edge[i].len;
        }
    }
    cout<<ans<<endl;
    return 0;
}
//kruskal算法模板