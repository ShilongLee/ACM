#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;
const int P=105;
const int N=505;
const int M=31000;
int p,n,v[M],first[M],ext[M],num,sum,master[N];
bool vis[N];//左侧编号1~p 右侧编号p+1~p+n，所以至少开p+n大小。
void add(int x,int y)
{
    v[++num]=y;
    ext[num]=first[x];
    first[x]=num;
}
bool match(int x)
{
    for(int i=first[x]; ~i; i=ext[i])
    {
        int y=v[i];
        if(!vis[y])
        {
            vis[y]=true;
            if(!master[y]||match(master[y]))
            {
                master[y]=x;
                return true;
            }
        }
    }
    return false;
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&p,&n);
        num=sum=0;
        memset(master,0,sizeof(master));
        memset(first,-1,sizeof(first));
        for(int i=1; i<=p; ++i)
        {
            int k;
            scanf("%d",&k);
            while(k--)
            {
                int y;
                scanf("%d",&y);
                add(i,p+y);
            }
        }
        for(int i=1; i<=p; ++i)
        {
            memset(vis,false,sizeof(vis));
            if(match(i))
                sum++;
        }
        if(sum==p)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
//hdu1083
