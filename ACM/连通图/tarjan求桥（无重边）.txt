#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<algorithm>
using namespace std;
const int N=10005;
const int M=N*20;
int n,v[M],first[M],ext[M],num,dfn[N],low[N],cnt,sum;
//bool readin[N];
struct Edge
{
    int x,y;
    bool operator<(const Edge &a)const
    {

        if(x!=a.x)
            return x<a.x;
        else
            return y<a.y;
    }
} edge[M];
void add(int x,int y)
{
    v[++num]=y;
    ext[num]=first[x];
    first[x]=num;
}
void tarjan(int st,int pre)
{
    dfn[st]=low[st]=++cnt;
    int child=0;
    for(int i=first[st]; ~i; i=ext[i])
    {
        int p=v[i];
        if(p==pre)
            continue;
        if(!dfn[p])
        {
            tarjan(p,st);
            low[st]=min(low[st],low[p]);
            if(low[p]>dfn[st])
                edge[++sum].x=min(st,p),edge[sum].y=max(st,p);
        }
        else
            low[st]=min(low[st],dfn[p]);
    }
}
int main()
{
    while(cin>>n)
    {
        if(n==0)
        {
            cout<<"0 critical links"<<endl<<endl;
            continue;
        }
        num=0,cnt=0,sum=0;
        memset(first,-1,sizeof(first));
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        //memset(readin,false,sizeof(readin));
        for(int i=1; i<=n; ++i)
        {
            int x,z,y;
            scanf("%d (%d)",&x,&z);
            x++;
            //readin[x]=true;
            for(int j=1; j<=z; ++j)
            {
                scanf("%d",&y);
                y++;
//                if(readin[y])
//                continue;
                add(x,y);
            }
        }
//        for(int i=first[1];~i;i=ext[i])
//            cout<<
        for(int i=1; i<=n; ++i)
            if(!dfn[i])
                tarjan(i,i);
//        cout<<"num="<<num<<endl;
//        for(int i=1; i<=n; ++i)
//        {
//            for(int j=first[i]; ~j; j=ext[j])
//            {
//                cout<<v[j]<<' ';
//            }
//            cout<<endl;
//        }
        sort(edge+1,edge+sum+1);
        cout<<sum<<" critical links"<<endl;
        for(int i=1; i<=sum; ++i)
            cout<<edge[i].x-1<<" - "<<edge[i].y-1<<endl;
        cout<<endl;
    }
    return 0;
}
//UVA-796
