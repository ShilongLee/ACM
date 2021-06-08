#include<stdio.h>
#include<string.h>
long long int mapp[55],dl[505],dr[505],n,a[15];
long long int sum=0;
void dfs(int step)
{
    if(step==n)
    {
        sum++;
        return ;
    }
    for(int i=0;i<n;i++)
    {
        if(!mapp[i]&&!dr[i+step]&&!dl[i-step+n])
        {
            mapp[i]=1;
            dr[i+step]=1;
            dl[i-step+n]=1;
            dfs(step+1);
            dr[i+step]=0;
            dl[i-step+n]=0;
            mapp[i]=0;
        }
    }
}
int main()
{
    for(n=1;n<=10;n++)
    {
        sum=0;
        memset(mapp,0,sizeof(mapp));
        memset(dl,0,sizeof(dl));
        memset(dr,0,sizeof(dr));
        dfs(0);
        a[n]=sum;
    }
    while(~scanf("%lld",&n)&&n)
    {
        printf("%lld\n",a[n]);
    }
}

//HUD 2553