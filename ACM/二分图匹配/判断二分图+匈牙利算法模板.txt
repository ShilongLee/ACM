#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
const int N=405;
const int M=40005;
int n,m,v[M],first[M],ext[M],num,group[M],sum,master[M],vis[M],flag;
void init()
{
    num=sum=flag=0;
    memset(first,-1,sizeof(first));
    memset(group,-1,sizeof(group));
    memset(master,0,sizeof(master));
    memset(vis,0,sizeof(vis));
}
void add(int x,int y)
{
    v[++num]=y;
    ext[num]=first[x];
    first[x]=num;
}
bool dfs(int st,int pre)
{
    for(int i=first[st]; ~i; i=ext[i])
    {
        int p=v[i];
        if(p==pre)
            continue;
        if(group[p]==-1)
        {
            group[p]=group[st]^1;
            if(!dfs(p,st))
                return false;
        }
        else if(group[p]==group[st])
            return false;
    }
    return true;
}
bool match(int x)
{
    for(int i=first[x]; ~i; i=ext[i])
    {
        int p=v[i];
        if(!vis[p])
        {
            vis[p]=true;
            if(!master[p]||match(master[p]))
            {
                master[p]=x;
                return true;
            }
        }
    }
    return false;
}
int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        init();
        for(int i=1; i<=m; ++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            add(x,y);
            add(y,x);
        }
        for(int i=1; i<=n; ++i)
            if(group[i]==-1)
            {
                group[i]=0;
                if(!dfs(i,i))
                {
                    printf("No\n");
                    flag=1;
                    break;
                }
            }
        if(flag)
            continue;
        for(int i=1; i<=n; ++i)
        {
            if(!group[i])
            {
                memset(vis,0,sizeof(vis));
                if(match(i))
                    sum++;
            }
        }
        printf("%d\n",sum);
    }
    return 0;
}
//hdu2444
