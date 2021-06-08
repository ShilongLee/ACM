#include<iostream>
#include<iomanip>
#include<string.h>
#include<math.h>
#include<stdio.h>
using namespace std;
const int inf=0x3f3f3f3f;
float mapp[202][202];
int vis[202];
float dis[202];
int locate[202];
int n;
float distance(float x1,float y1,float x2,float y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
void dij(int st,int ed,int num)
{
    memset(vis,0,sizeof(vis));
    for(int i=1; i<=n; ++i)
        dis[i]=mapp[1][i];
    dis[1]=0;
    float minn;
    int k;
    vis[1]=1;
    for(int i=1; i<=n; ++i)
    {
        minn=inf;
        for(int j=1; j<=n; ++j)
        {
            if(!vis[j]&&dis[j]<minn)
            {
                minn=dis[j];
                k=j;
            }
        }
        if(minn==inf)
            break;
        vis[k]=1;
        for(int j=1; j<=n; ++j)
            if(!vis[j])
                dis[j]=min(dis[j],max(dis[k],mapp[k][j]));
    }
    printf("Scenario #%d\nFrog Distance = %.3f\n\n",num,dis[2]);
}
int main()
{
    int t=0;
    while(cin>>n&&n)
    {
        ++t;
        memset(mapp,inf,sizeof(mapp));
        int x,y;
        for(int i=1; i<=n; ++i)
        {
            cin>>x>>y;
            locate[i]=x*10000+y;
        }
        for(int i=1; i<=n; ++i)
            for(int j=1; j<=n; ++j)
            {
                int x1=locate[i]/10000;
                int y1=locate[i]%10000;
                int x2=locate[j]/10000;
                int y2=locate[j]%10000;
                mapp[i][j]=distance(x1,y1,x2,y2);
            }
        /*for(int k=1; k<=n; ++k)
            for(int i=1; i<=n; ++i)
                for(int j=1; j<=n; ++j)
                {
                    mapp[i][j]=min(mapp[i][j],max(mapp[i][k],mapp[k][j]));
                }*/floyd
        printf("Scenario #%d\nFrog Distance = %.3f\n\n",t,mapp[1][2]);
        //dij(1,2,t);//dij
    }
}

//POJ 2253