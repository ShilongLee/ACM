#include<iostream>
#include<queue>
using namespace std;
char mapp[35][35][35];
int L,R,C,flag=0;;
int dir[6][3]={1,0,0,-1,0,0,0,-1,0,0,1,0,0,0,-1,0,0,1};
struct node
{
    int L,R,C,step;
}S,E,now,ext;
void bfs(node a)
{
    queue<node>q;
    q.push(a);
    while(!q.empty())
    {
        now=q.front();
        q.pop();
        if(now.L==E.L&&now.C==E.C&&now.R==E.R)
        {
            flag=1;
            cout<<"Escaped in "<<now.step<<" minute(s)."<<endl;
        }
        for(int i=0;i<6;i++)
        {
            ext.L=now.L+dir[i][0];
            ext.R=now.R+dir[i][1];
            ext.C=now.C+dir[i][2];
            ext.step=now.step+1;
            if(mapp[ext.L][ext.R][ext.C]=='.'&&ext.L<L&&ext.L>=0&&ext.R<R&&ext.R>=0&&ext.C<C&&ext.C>=0)
            {
                mapp[ext.L][ext.R][ext.C]='#';
                q.push(ext);
            }
        }
    }
}
int main()
{
    while(cin>>L>>R>>C&&L&&R&&C)
    {
        flag=0;
        for(int i=0;i<L;i++)
            for(int j=0;j<R;j++)
            for(int k=0;k<C;k++)
        {
            cin>>mapp[i][j][k];
            if(mapp[i][j][k]=='S')
            {
                mapp[i][j][k]='.';
                S.L=i;
                S.R=j;
                S.C=k;
            }
             else if(mapp[i][j][k]=='E')
            {
                mapp[i][j][k]='.';
                E.L=i;
                E.R=j;
                E.C=k;
            }
        }
        S.step=0;
        bfs(S);
        if(!flag)
            cout<<"Trapped!"<<endl;
    }
}


//POJ 2251