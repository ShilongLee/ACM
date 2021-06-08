#include<stdio.h>
#include<string.h>
using namespace std;
int vis[5005];
int a[5005];
int n;
void f(int x)
{
    if(x==n+1)
    {
        for(int i=1; i<=n; i++)
            printf("%d ",a[i]);
            printf("\n");
            return ;
        }
        for(int i=1;i<=n;i++)
        {
            if(!vis[i])
            {
                vis[i]=1;
                a[x]=i;
                f(x+1);
                vis[i]=0;
            }
        }
}
int main()
{
    while(~scanf("%d",&n))
{
        memset(vis,0,sizeof(vis));
        memset(a,0,sizeof(a));
        f(1);
    }
}
