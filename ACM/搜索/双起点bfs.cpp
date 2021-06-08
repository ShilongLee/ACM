#include<stdio.h>
#include<iostream>
#include<string.h>
#include<queue>
using namespace std;
int n,m;
char mapp[15][15];
int vis[15][15];
int viss[15][15];
int dir[4][2]= {1,0,-1,0,0,1,0,-1};
const int inf=0xfffffff;
struct node
{
    int x,y,step;
};
void conbfs(int x,int y,int conpath)//寻找联通区块数
{
    node st;
    st.x=x;
    st.y=y;
    st.step=0;
    queue<node>qu;
    qu.push(st);
    while(!qu.empty())
    {
        node now;
        now=qu.front();
        qu.pop();
        node ext;
        for(int i=0; i<4; i++)
        {
            ext.x=now.x+dir[i][0];
            ext.y=now.y+dir[i][1];
            if(ext.x>=1&&ext.x<=n&&ext.y>=1&&ext.y<=m&&mapp[ext.x][ext.y]=='#'&&!viss[ext.x][ext.y])
            {
                viss[ext.x][ext.y]=conpath;
                qu.push(ext);
            }
        }
    }
}
int burnbfs(int x1,int y1,int x2,int y2)//向四周扩散找最大数为所需步数，双起点开始，两个起点步数都为1.
{
    node st,st2;
    st.x=x1;
    st.y=y1;
    st.step=0;
    vis[x1][y1]=1;
    vis[x2][y2]=1;
    st2.x=x2;
    st2.y=y2;
    st2.step=0;
    int k=0;
    queue<node>qu;
    qu.push(st);
    qu.push(st2);
    while(!qu.empty())
    {
        node now=qu.front();
        qu.pop();
        node ext;
        k=max(k,now.step);
        for(int i=0; i<4; i++)
        {
            ext.x=now.x+dir[i][0];
            ext.y=now.y+dir[i][1];
            ext.step=now.step+1;
            if(ext.x>=1&&ext.x<=n&&ext.y>=1&&ext.y<=m&&mapp[ext.x][ext.y]=='#'&&!vis[ext.x][ext.y])
            {
                vis[ext.x][ext.y]=1;
                qu.push(ext);
            }
        }
    }
    return k;
}
int main()
{
    int t;
    cin>>t;
    for(int k=1; k<=t; k++)
    {
        memset(viss,0,sizeof(viss));
        int conpath=0;
        cin>>n>>m;
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)
                cin>>mapp[i][j];
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)
            {
                if(mapp[i][j]=='#'&&!viss[i][j])
                {
                    conpath+=1;
                    conbfs(i,j,conpath);
                    viss[i][j]=conpath;
                }
            }
        if(conpath>2)
        {
            printf("Case %d: %d\n",k,-1);
            continue;
        }
        else if(conpath==0)
        {
            printf("Case %d: %d\n",k,0);
            continue;
        }
        /*for(int i=1; i<=n; i++)
        {
           for(int j=1; j<=m; j++)
           cout<<viss[i][j]<<' ';
           cout<<endl;
        }*/
        int maxstep=inf;
        for(int x1=1; x1<=n; x1++)
        {
            for(int y1=1; y1<=m; y1++)
            {
                for(int x2=1; x2<=n; x2++)
                {
                    for(int y2=1; y2<=m; y2++)
                    {
                        if(mapp[x1][y1]=='#'&&mapp[x2][y2]=='#'&&viss[x1][y1]==1&&viss[x2][y2]==conpath)
                        {
                            memset(vis,0,sizeof(vis));
                            maxstep=min(maxstep,burnbfs(x1,y1,x2,y2));
                        }
                    }
                }
            }
        }
        printf("Case %d: %d\n",k,maxstep);
    }
}

//FZU 2150