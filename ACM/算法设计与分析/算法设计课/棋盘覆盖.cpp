#include<stdio.h>
#include<string.h>
int n;
int sum=0;
int mapp[5005][5005];
void fillmapp(int tr,int tc,int dr,int dc,int sizee)
{
    if(sizee==1) return ;
    int t=++sum;
    int s=sizee/2;
    if(dr<tr+s&&dc<tc+s)
        fillmapp(tr,tc,dr,dc,s);
    else
    {
        mapp[tr+s-1][tc+s-1]=t;
        fillmapp(tr,tc,tr+s-1,tc+s-1,s);
    }
    if(dr<tr+s&&dc>=tc+s)
        fillmapp(tr,tc+s,dr,dc,s);
    else
    {
        mapp[tr+s-1][tc+s]=t;
        fillmapp(tr,tc+s,tr+s-1,tc+s,s);
    }
    if(dr>=tr+s&&dr<tc+s)
        fillmapp(tr+s,tc,dr,dc,s);
    else
    {
        mapp[tr+s][tc+s-1]=t;
        fillmapp(tr+s,tc,tr+s,tc+s-1,s);
    }
    if(dr>=tr+s&&dr>=tc+s)
        fillmapp(tr+s,tc+s,dr,dc,s);
    else
    {
        mapp[tr+s][tc+s]=t;
        fillmapp(tr+s,tc+s,tr+s,tc+s,s);
    }
}
int main()
{
    while(~scanf("%d",&n))
    {
        int m=n,flag=0;
        while(m>1)
        {
            if(m%2==0)
                m/=2;
            else
            {
                flag=1;
                break;
            }
        }
        if(flag)
        {
            printf("n必须为2的指数倍！\n");
            continue ;
        }
        int x,y;
        sum=0;
        scanf("%d%d",&x,&y);
        memset(mapp,0,sizeof(mapp));
        fillmapp(1,1,x,y,n);
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
                printf("%d ",mapp[i][j]);
            printf("\n");
        }
    }
}
