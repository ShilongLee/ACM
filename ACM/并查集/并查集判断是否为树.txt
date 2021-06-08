#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;
const int N=100005;
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
    int a,b;
    for(int i=0; i<N; ++i)
        rt[i]=i;
    int flag=0;
    int edge=0;
    int node=0;
    memset(vis,0,sizeof(vis));
    int num=1;
    while(cin>>a>>b)
    {
        if(!vis[a]&&a)
        {
            node++;
            vis[a]=1;
        }
        if(!vis[b]&&b)
        {
            node++;
            vis[b]=1;
        }
        if(a!=b)
            edge++;
        if(a==0&&b==0)
        {
            if(node!=edge+1)
                flag=1;
            if(node==0)
                flag=0;
            if(flag)
                cout<<"No"<<endl;
            else
                cout<<"Yes"<<endl;
            memset(vis,0,sizeof(vis));
            for(int i=0; i<N; ++i)
                rt[i]=i;
            flag=0;
            edge=0;
            node=0;
            continue;
        }
        else if(a==-1&&b==-1)
            break;
        int xx=fin(a);
        int yy=fin(b);
        if(xx==yy)
            flag=1;
        else
            rt[xx]=yy;
    }
    return 0;
}
//hdu 1272