#include<iostream>
#include<string.h>
using namespace std;
const int N=105;
const int M=4505;
int mapp[N][N];
int n,m;
int main()
{
    memset(mapp,0,sizeof(mapp));
    cin>>n>>m;
    for(int i=1; i<=m; ++i)
    {
        int x,y;
        cin>>x>>y;
        mapp[x][y]=1;
        mapp[y][x]=2;
    }
    for(int k=1; k<=n; ++k)
        for(int i=1; i<=n; ++i)
            for(int j=1; j<=n; ++j)
            {
                if(mapp[i][j]==0)
                {
                    if(mapp[i][k]==mapp[k][j])
                        mapp[i][j]=mapp[i][k];
                }
            }
    int summ=0;
    for(int i=1; i<=n; ++i)
    {
        int sum=0;
        for(int j=1; j<=n; ++j)
            if(mapp[i][j])
                sum++;
        if(sum==n-1)
            summ++;
    }
    cout<<summ<<endl;
}
//u-->v=1代表u>v  u-->v=2代表u<v  当一个节点的与除自身的其他所有节点确定大小关系时，说明这个点的位置确定。
//poj3660
//传递闭包