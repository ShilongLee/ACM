#include<stdio.h>
#include<string.h>
const int N=50005;
int rt[N];
int n,k;
int dis[N];
int fin(int x)
{
    if(rt[x]==x)
        return x;
    int root=fin(rt[x]);
    dis[x]=(dis[x]+dis[rt[x]])%3;
    return rt[x]=root;
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1; i<=n; ++i)
        rt[i]=i;
    memset(dis,0,sizeof(dis));
    int sum=0;
    int d,x,y;
    while(k--)
    {
        scanf("%d%d%d",&d,&x,&y);
        if(x>n||y>n)
        {
            sum++;
            continue;
        }
        if(d==2&&x==y)
        {
            sum++;
            continue;
        }
        int xx=fin(x);
        int yy=fin(y);
        if(xx==yy)
        {
            int g=(dis[x]-dis[y]+3)%3;
            if(d==1&&g!=0)
            {
                sum++;
                continue;
            }
            else if(d==2&&g!=1)
            {
                sum++;
                continue;
            }
        }
        else
        {
                rt[xx]=yy;
                dis[xx]=(dis[y]-dis[x]+d-1+3)%3;
        }
    }
    printf("%d\n",sum);
}
//poj 1182
//和上一题一样还是一道带权并查集的题，用权值储存每个点与其父结点的关系，0表示同类，1表示吃父结点，2则是被父结点吃。