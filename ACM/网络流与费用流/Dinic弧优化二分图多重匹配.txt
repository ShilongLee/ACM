#include<iostream>
#include<algorithm>
#include<queue>
#include<string>
#include<stdio.h>
#include<vector>
#include<string.h>
using namespace std;
const int N=1005;
const int M=505;
const int inf=0x3f3f3f3f;
const int MAXM=N*M<<1;
int n,m,v[MAXM],w[MAXM],first[MAXM],ext[MAXM],num,mid,st,ed,depth[MAXM],cur[MAXM];
vector<int>ve[MAXM];
void add(int x,int y,int z)
{
    v[++num]=y;
    w[num]=z;
    ext[num]=first[x];
    first[x]=num;
}
void build()
{
    memset(first,-1,sizeof(first));
    num=1;
    for(int i=0; i<n; ++i)
    {
        add(st,i,1),add(i,st,0);//0~n-1为左侧点、n~n+m-1为右侧点
        int siz=ve[i].size();
        for(int j=0; j<siz; ++j)
            add(i,ve[i][j],1),add(ve[i][j],i,0);
    }
    for(int i=n; i<n+m; ++i)
        add(i,ed,mid),add(ed,i,0);
}
bool bfs()
{
    memset(depth,-1,sizeof(depth));
    queue<int>q;
    depth[st]=1;
    q.push(st);
    while(!q.empty())
    {
        int f=q.front();
        q.pop();
        for(int i=first[f]; ~i; i=ext[i])
        {
            int p=v[i];
            if(w[i]&&depth[p]==-1)
            {
                depth[p]=depth[f]+1;
                q.push(p);
            }
        }
    }
    if(depth[ed]==-1)
        return false;
    return true;
}
int dfs(int st,int flow)
{
    if(st==ed)
        return flow;
    int sum=0;
    for(int &i=cur[st]; ~i; i=ext[i])/** 当前弧优化*/
    {
        int p=v[i];
        if(w[i]&&depth[p]==depth[st]+1)//dinic分层 只能向下一层走
        {
            int t=dfs(p,min(flow,w[i]));//向下分的流量
            w[i]-=t;
            w[i^1]+=t;
            flow-=t;
            sum+=t;
            if(flow==0) return sum;/** 优化部分 当边流量特别少的时候优化较大，流量一下就用完了，就不用搜索剩下的边了*/
        }
    }
    if(!sum)
        depth[st]=-1;
    return sum;
}
bool dinic()
{
    build();
    int ans=0,res;
    while(bfs())
    {
        memcpy(cur,first,sizeof(first));/** 当前弧优化*/
        ans+=dfs(st,inf);
    }
    if(ans==n)
        return true;
    return false;
}
int main()
{
    while(scanf("%d%d",&n,&m)&&(n||m))
    {
        num=1,st=n+m,ed=st+1;
        for(int i=0; i<n+5; ++i)
            ve[i].clear();
        for(int i=0; i<n; ++i)
        {
            char s[20];
            char c;
            scanf("%s",s);
            while(1)
            {
                int y;
                scanf("%d",&y);
                c=getchar();
                ve[i].push_back(y+n);
                if(c=='\n')
                    break;
            }
        }
        int l=0,r=n;
        while(l<=r)
        {
            mid=(l+r)>>1;
            if(dinic())
                r=mid-1;
            else
                l=mid+1;
        }
        printf("%d\n",l);
    }
    return 0;
}
//poj2289
