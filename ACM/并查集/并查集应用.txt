#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
const int N=10005;
int n;
struct node
{
    int profit;
    int deadline;
} product[N];
bool cmp(node a,node b)
{
    return a.profit>b.profit;
}
int rt[N];
int vis[N];
int fin(int x)
{
    if(rt[x]==x)
        return x;
    return rt[x]=fin(rt[x]);
}
int main()
{
    while(cin>>n)
    {
        memset(vis,0,sizeof(vis));
        for(int i=1; i<=n; ++i)
            cin>>product[i].profit>>product[i].deadline;
        for(int i=1; i<N; ++i)
            rt[i]=i;
        sort(product+1,product+n+1,cmp);
        long long sum=0;
        for(int i=1; i<=n; ++i)
        {
            int xx=fin(product[i].deadline);
            if(!vis[xx])
            {
                vis[xx]=1;
                if(xx==1)
                    rt[xx]=1;
                else
                    rt[xx]=fin(xx-1);
                sum+=product[i].profit;
            }
        }
        cout<<sum<<endl;
    }
}
//poj1456
