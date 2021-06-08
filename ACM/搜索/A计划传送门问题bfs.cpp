#include<stdio.h>
#include<iostream>
#include<queue>
#include<string.h>
using namespace std;
int N,M,T,ex,ey,ez,ok=0;
const int maxn=13;
char mapp[maxn][maxn][5];
int dir[4][2]= {0,1,1,0,0,-1,-1,0};
int vis[maxn][maxn][5];
struct node
{
    int x,y,z,step;
} st,cur,ext;
void bfs(node qu)
{
    queue<node>q;
    q.push(qu);
    while(!q.empty())
    {
        cur=q.front();
        q.pop();
        if(cur.x==ex&&cur.y==ey&&cur.z==ez&&cur.step<=T)
        {
            ok=1;
            return ;
        }
        for(int i=0; i<4; i++)
        {
            ext.x=cur.x+dir[i][0];
            ext.y=cur.y+dir[i][1];
            ext.z=cur.z;
            ext.step=cur.step+1;
            if(ext.x<1||ext.x>N||ext.y<1||ext.y>M||vis[ext.x][ext.y][ext.z]==1||mapp[ext.x][ext.y][ext.z]=='*')
                continue ;
            if(mapp[ext.x][ext.y][ext.z]=='#')
                ext.z^=1;
            if(mapp[ext.x][ext.y][ext.z]!='*'&&ext.step<=T)
            {
                vis[ext.x][ext.y][ext.z]=1;
                q.push(ext);
            }
        }
    }
}
int main()
{
    int  t;
    scanf("%d",&t);
    while(t--)
    {
        ok=0;
        memset(vis,0,sizeof(vis));
        scanf("%d%d%d",&N,&M,&T);
        for(int z=0; z<=1; z++)
            for(int i=1; i<=N; i++)
                for(int j=1; j<=M; j++)
                    scanf(" %c",&mapp[i][j][z]);
        for(int i=1; i<=N; i++)
            for(int j=1; j<=M; j++)
            {
                if((mapp[i][j][0]=='*'||mapp[i][j][0]=='#')&&(mapp[i][j][1]=='#'||mapp[i][j][1]=='*'))
                {
                    mapp[i][j][0]='*';
                    mapp[i][j][0]='*';
                }
                if(mapp[i][j][1]=='P')
                {
                    ex=i;
                    ey=j;
                    ez=1;
                }
                if(mapp[i][j][0]=='P')
                {
                    ex=i;
                    ey=j;
                    ez=0;
                }
            }
        vis[1][1][0]=1;
        st.x=1;
        st.y=1;
        st.z=0;
        st.step=0;
        bfs(st);
        if(ok)
            printf("YES\n");
        else printf("NO\n");
    }
}

\\HDU 2102