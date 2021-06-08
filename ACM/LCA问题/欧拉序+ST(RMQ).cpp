#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
const int N=500005;
const int M=500005;
int n,m,st;
int v[N<<1],first[N<<1],ext[N<<1],num,tot;
int depth[N];
int df[N];
int dl[N];
int a[N<<2];
int dpmin[N<<2][50];
void add(int x,int y)
{
    v[++num]=y;
    ext[num]=first[x];
    first[x]=num;
}
void dfs(int st,int pre)//欧拉序
{
    depth[st]=depth[pre]+1;
    a[++tot]=st;
    df[st]=tot;
    for(int i=first[st]; i!=-1; i=ext[i])
    {
        int p=v[i];
        if(p==pre)
            continue;
        dfs(p,st);
        a[++tot]=st;
    }
    dl[st]=tot;
}
int main()
{
    num=0;
    tot=0;
    memset(depth,0,sizeof(depth));
    memset(first,-1,sizeof(first));
    cin>>n>>m>>st;
    for(int i=1; i<=n-1; ++i)
    {
        int x,y;
        cin>>x>>y;
        add(x,y);
        add(y,x);
    }
    dfs(st,st);
    for(int i=1; i<=tot; ++i) //可以省略a[i]，直接把数放到dpmin。
        dpmin[i][0]=a[i];
    for(int j=1; (1<<j)<=tot; ++j)//区间内深度最小的
        for(int i=1; i+(1<<j)-1<=tot; ++i)
        {
            if(depth[dpmin[i][j-1]]<=depth[dpmin[i+(1<<(j-1))][j-1]])
                dpmin[i][j]=dpmin[i][j-1];
            else
                dpmin[i][j]=dpmin[i+(1<<(j-1))][j-1];
        }
    while(m--)
    {
        int x,y;
        cin>>x>>y;
        if(dl[x]>dl[y])//链式前向星从最后一条边开始，所以区间反着的，所以是最后出现时候的区间。
            swap(x,y);
        int l=dl[x];
        int r=dl[y];
        int k=0;
        while((1<<(k+1))<=r-l+1)
            k++;
        int ans1=dpmin[l][k];
        int ans2=dpmin[r-(1<<k)+1][k];
        if(depth[ans1]<=depth[ans2])
            cout<<ans1<<endl;
        else
            cout<<ans2<<endl;
    }
}
//洛谷3379