#include<iostream>
#include<iomanip>
#include<string.h>
#include<math.h>
#include<stdio.h>
using namespace std;
const int inf=0x3f3f3f3f;
int mapp[202][202];
int vis[202];
int main()
{
    int n;
    while(cin>>n)
    {
        memset(mapp,inf,sizeof(mapp));
        for(int i=1; i<=n; ++i)
            for(int j=1; j<=n; ++j)
                cin>>mapp[i][j];
    }
    for(int k=1; k<=n; ++k)
        for(int i=1; i<=n; ++i)
            for(int j=1; j<=n; ++j)
                mapp[i][j]=min(mapp[i][j],mapp[i][k]+mapp[k][j]);
    int st,en;
    cin>>st>>en;
    if(mapp[st][en])
        cout<<mapp[st][en]<<endl;
    else
        cout<<-1<<endl;
}
//首先，它是运用了动态规划的思想来进行问题求解。动态规划解题的关键在于找好子结构。Floyd构造的结构非常巧妙：找i和j之间通过编号不超过k（k从1到n）的节点的最短路径（一定要注意，这里是当前最短路径，当k=n时达到最终最短路径）。为了便于说明，我们可以弄一个三维数组f[k][i][j]表示i和j之间可以通过编号不超过k的节点的“最短路径”。对于k-1到k，只有两种可能，经过编号为k的点，要么不能找到一条从i到j的更短路，此时有f[k][i][j] = f[k-1][i][j] ；要么能找到，那这个最短路径一定是d[i][k]+d[k][j]，那么就用这个较小的距离去更新d[i][j]。综合以上两种情况，f[k][i][j] = min(f[k-1][i][j] , f[k-1][i][k]+f[k-1][k][j])。