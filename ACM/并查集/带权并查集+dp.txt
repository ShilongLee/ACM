#include<iostream>
#include<string.h>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;
int dis[1010];
int n,p1,p2;
int rt[1010];
vector<int>tree[1010];
vector<int>group_0[1010];
vector<int>group_1[1010];
int dp[1010][1010];
struct node
{
    int a,b;
} group_num[1010];
int fin(int x)
{
    if(rt[x]==x)
        return x;
    int root=fin(rt[x]);
    dis[x]^=dis[rt[x]];
    return rt[x]=root;
}
void join(int x,int y,int r)
{
    int xx=fin(x);
    int yy=fin(y);
    if(xx!=yy)
    {
        rt[xx]=yy;
        dis[xx]=dis[x]^dis[y]^r;
    }
}
void init()
{
    memset(dp,0,sizeof(dp));
    for(int i=1; i<=1005; ++i)
    {
        rt[i]=i;
        dis[i]=0;
        group_0[i].clear();
        group_1[i].clear();
        tree[i].clear();
    }
}
int main()
{
    while(cin>>n>>p1>>p2)
    {
        if(!n&&!p1&&!p2)
            break;
        init();
        for(int i=1; i<=n; ++i)
        {
            int a,b;
            string s;
            cin>>a>>b>>s;
            if(s=="yes")
                join(a,b,0);
            else
                join(a,b,1);
        }
        if(p1==p2)
        {
            cout<<"no"<<endl;
            continue;
        }
        for(int i=1; i<=p1+p2; ++i)
            tree[fin(i)].push_back(i);
        int cnt=1;
        for(int i=1; i<=p1+p2; ++i)
        {
            int s=tree[i].size();
            int num=0;
            if(s)
            {
                for(int j=0; j<s; ++j)
                {
                    if(!dis[tree[i][j]])
                    {
                        group_0[cnt].push_back(tree[i][j]);
                        num++;
                    }
                    else
                        group_1[cnt].push_back(tree[i][j]);
                }
                group_num[cnt].a=num;
                group_num[cnt].b=s-num;
                cnt++;
            }
        }
        dp[0][0]=1;
        for(int i=1; i<cnt; ++i)
            for(int j=0; j<=p1; ++j)
            {
                if(j-group_num[i].a>=0)
                    dp[i][j]+=dp[i-1][j-group_num[i].a];
                if(j-group_num[i].b>=0)
                    dp[i][j]+=dp[i-1][j-group_num[i].b];
            }
//        for(int i=0; i<cnt; i++)
//        {
//            for(int j=0; j<=p1; j++)
//                cout<<dp[i][j]<<' ';
//            cout<<endl;
//        }
        if(dp[cnt-1][p1]!=1)
        {
            cout<<"no"<<endl;
            continue;
        }
        int ans[1010];
        int num=0;
        int v=p1;
        for(int i=cnt-1; i>=1; --i)
        {
            if(dp[i-1][v-group_num[i].a]==1)
            {
                for(int j=0; j<group_0[i].size(); ++j)
                    ans[num++]=group_0[i][j];
                v-=group_num[i].a;
            }
            else
            {
                for(int j=0; j<group_1[i].size(); ++j)
                    ans[num++]=group_1[i][j];
                v-=group_num[i].b;
            }
        }
        sort(ans,ans+num);
        for(int i=0; i<num; ++i)
            cout<<ans[i]<<endl;
        cout<<"end"<<endl;
    }
    return 0;
}
//poj 1417