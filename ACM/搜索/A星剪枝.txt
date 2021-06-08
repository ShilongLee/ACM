#include<stdio.h>
#include<algorithm>
#include<iostream>
#include<string.h>
#include<queue>
using namespace std;
int m,n,k,d;
bool vis[105][105][1005];//同一时间不能再同一位置
int dir[4][2]= {0,1,1,0,0,-1,-1,0};
int mapp[105][105];
struct castle
{
    char dir;
    int t,v,x,y;
} c[10005];
struct node
{
    int x,y;
    int step;
    int h;
    bool operator<(const node &a)const
    {
        return a.h<h;
    }
};
int man(int x,int y)
{
    return (m-x)+(n-y);
}
void bfs(int x,int y,int step)
{
    node st;
    st.x=x;
    st.y=y;
    st.step=step;
    st.h=st.step+man(st.x,st.y);
    priority_queue<node>qu;
    qu.push(st);
    while(!qu.empty())
    {
        node now=qu.top();
        qu.pop();
        if(now.x==m&&now.y==n)
        {
            cout<<now.step<<endl;
            return;
        }
        for(int i=0; i<5; i++)
        {
            node ext;
                ext.x=now.x+dir[i][0];
                ext.y=now.y+dir[i][1];
                ext.step=now.step+1;
                if(ext.x>=0&&ext.x<=m&&ext.y>=0&&ext.y<=n&&!vis[ext.x][ext.y][ext.step]&&mapp[ext.x][ext.y]==-1)
                {
                    int flag=0;
                    for(int k=ext.x-1; k>=0; k--)
                    {
                        if(mapp[k][ext.y]!=-1&&c[mapp[k][ext.y]].dir=='S')
                        {
                            if((ext.x-k)>ext.step*c[mapp[k][ext.y]].v)
                                break;
                            if((ext.x-k)%c[mapp[k][ext.y]].v)
                                break;
                            if((ext.step-(ext.x-k)/c[mapp[k][ext.y]].v)%c[mapp[k][ext.y]].t==0)
                            {
                                flag=1;
                                break;
                            }
                        }
                        if(mapp[k][ext.y]!=-1)
                            break;
                    }
                    if(flag)
                        continue;
                    for(int k=ext.x+1; k<=m; k++)
                    {
                        if(mapp[k][ext.y]!=-1&&c[mapp[k][ext.y]].dir=='N')
                        {
                            if((k-ext.x)>ext.step*c[mapp[k][ext.y]].v)
                                break;
                            if((k-ext.x)%c[mapp[k][ext.y]].v)
                                break;
                            if((ext.step-(k-ext.x)/c[mapp[k][ext.y]].v)%c[mapp[k][ext.y]].t==0)
                            {
                                flag=1;
                                break;
                            }
                        }
                        if(mapp[k][ext.y]!=-1)
                            break;
                    }
                    if(flag)
                        continue;
                    for(int k=ext.y+1; k<=n; k++)
                    {
                        if(mapp[ext.x][k]!=-1&&c[mapp[ext.x][k]].dir=='W')
                        {
                            if((k-ext.y)>ext.step*c[mapp[ext.x][k]].v)
                                break;
                            if((k-ext.y)%c[mapp[ext.x][k]].v)
                                break;
                            if((ext.step-(k-ext.y)/c[mapp[ext.x][k]].v)%c[mapp[ext.x][k]].t==0)
                            {
                                flag=1;
                                break;
                            }
                        }
                        if(mapp[ext.x][k]!=-1)
                            break;
                    }
                    if(flag)
                        continue;
                    for(int k=ext.y-1; k>=0; k--)
                    {
                        if(mapp[ext.x][k]!=-1&&c[mapp[ext.x][k]].dir=='E')
                        {
                            if((ext.y-k)>ext.step*c[mapp[ext.x][k]].v)
                                break;
                            if((ext.y-k)%c[mapp[ext.x][k]].v)
                                break;
                            if((ext.step-(ext.y-k)/c[mapp[ext.x][k]].v)%c[mapp[ext.x][k]].t==0)
                            {
                                flag=1;
                                break;
                            }
                        }
                        if(mapp[ext.x][k]!=-1)
                            break;
                    }
                    if(flag)
                        continue;
                    ext.h=ext.step+man(ext.x,ext.y);
                    if(ext.h>=d)
                        continue;
                    vis[ext.x][ext.y][ext.step]=1;
                    qu.push(ext);
                }
            }
    }
    cout<<"Bad luck!"<<endl;
}
int main()
{
    while(cin>>m>>n>>k>>d)
    {
        memset(mapp,-1,sizeof(mapp));
        memset(vis,0,sizeof(vis));
        for(int i=0; i<k; i++)
        {
            cin>>c[i].dir>>c[i].t>>c[i].v>>c[i].x>>c[i].y;
            mapp[c[i].x][c[i].y]=i;
        }
        vis[0][0][0]=1;
        bfs(0,0,0);
        /*for(int i=0;i<=m;i++)
        {
            for(int j=0;j<=n;j++)
                cout<<p[i][j].x<<' '<<p[i][j].y<<"    ";
            cout<<endl;
        }*/
    }
}

//hdu 3533