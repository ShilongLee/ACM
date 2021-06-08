#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int inf=0x3f3f3f3f;
struct node
{
    int x,y,len;
} edge[5005];
int rt[105];
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
int n;
int main()
{
    while(~scanf("%d",&n)&&n)
    {
        int m=n*(n-1)/2;
        for(int i=1; i<=m; ++i)
            scanf("%d%d%d",&edge[i].x,&edge[i].y,&edge[i].len);
        sort(edge+1,edge+m+1,cmp);
        int ans=0;
        for(int i=1; i<=n; ++i)
            rt[i]=i;
        for(int i=1; i<=m; ++i)
        {
            int xx=fin(edge[i].x);
            int yy=fin(edge[i].y);
            if(xx!=yy)
            {
                rt[xx]=yy;
                ans+=edge[i].len;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
//hud1233
