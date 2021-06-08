#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
const int N=10;
const int M=1005;
int n;
int xid[N][N];
int yid[N][N];
int mapp[N][N];
int v[M],first[M],ext[M],num,sum,like[M],p[M];
bool vis[M];
void add(int x,int y)
{
    v[++num]=y;
    ext[num]=first[x];
    first[x]=num;
}
bool scc(int x)
{
    for(int i=first[x]; ~i; i=ext[i])
    {
        int k=v[i];
        if(!vis[k])
        {
            vis[k]=true;
            if(!p[k]||scc(p[k]))
            {
                p[k]=x;
                like[x]=k;
                return true;
            }
        }
    }
    return false;
}
int main()
{
    while(cin>>n&&n)
    {
        num=sum=0;
        memset(like,0,sizeof(like));
        memset(first,-1,sizeof(first));
        memset(p,0,sizeof(p));
        memset(mapp,0,sizeof(mapp));
        memset(xid,0,sizeof(xid));
        memset(yid,0,sizeof(yid));
        char c;
        int l;
        for(int i=1; i<=n; ++i)
            for(int j=1; j<=n; ++j)
            {
                cin>>c;
                if(c=='X')
                    mapp[i][j]=1;
            }
        int cnt=0;
        for(int i=1; i<=n; ++i)
        {
            cnt++;
            for(int j=1; j<=n; ++j)
            {
                if(mapp[i][j])
                {
                    cnt++;
                    continue;
                }
                xid[i][j]=cnt;
            }
        }
        l=cnt;
        for(int i=1; i<=n; ++i)
        {
            cnt++;
            for(int j=1; j<=n; ++j)
            {
                if(mapp[j][i])
                {
                    cnt++;
                    continue;
                }
                yid[j][i]=cnt;
            }
        }
        for(int i=1; i<=n; ++i)
            for(int j=1; j<=n; ++j)
            {
                if(xid[i][j]&&yid[i][j])
                    add(xid[i][j],yid[i][j]);
            }
        for(int i=1; i<=l; ++i)
        {
            memset(vis,0,sizeof(vis));
            if(scc(i))
            {
                sum++;
            }
        }

        cout<<sum<<endl;
    }
    return 0;
}
//hdu1045
//此题可以直接枚举，但如果数据更大的话，就需要用二分图来解了：
//
//1.对于每一行，把连通的部分缩成一个点，并为之编号xid。同理，每一列也如此yid。
//
//2.如果a[x][y]是空格，那么就在点xid[x][y]与点yid[x][y]之间连一条边。表明：如果在[x][y]处放置一个棋子，那么在点xid[x][y]和点yid[x][y]所涉及到的区域里，已经存在着攻击，所以不能再放其他棋子。
//
//3.求出最大匹配数，就是x坐标与y坐标的最大组合数，每一对组合，都代表着一个可放置点（影响的范围为一段区域），所以最大匹配数，即为最大放置数。
