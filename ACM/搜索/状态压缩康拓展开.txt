#include<stdio.h>
#include<string>
#include<iostream>
#include<string.h>
#include<algorithm>
#include<math.h>
#include<queue>
#include<vector>
#include<stack>
#define maxn 362885
using namespace std;
const int fact[]= {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
int seq[15];
int vis[maxn];
string path[maxn];
int dir[4][2]= {0,1,1,0,0,-1,-1,0};
char ddir[4]= {'l','u','r','d'};
struct node
{
    string path;
    int x,y,ash;
};
int contor()//康托展开
{
    int sum=0;
    for(int i=1; i<=8; i++)
    {
        int l=0;
        for(int j=i+1; j<=9; j++)
            if(seq[j]<seq[i])
                l++;
        sum+=l*(fact[9-i]);
    }
    return sum;
}
void decontor(int sum)//逆康托展开
{
    vector<int >v;
    for(int i=1; i<=9; i++)
        v.push_back(i);
    for(int i=1; i<=9; i++)
    {
        int x=sum%(fact[9-i]);
        int y=sum/(fact[9-i]);
        sum=x;
        seq[i]=v[y];
        v.erase(v.begin()+y);
    }
}
void bfs()
{
    for(int i=1; i<=9; i++)
        seq[i]=i;
    node st;
    st.x=3;
    st.y=3;
    st.ash=0;
    st.path="";
    vis[0]=1;
    path[0]="";
    queue<node>qu;
    qu.push(st);
    while(!qu.empty())
    {
        node now=qu.front();
        qu.pop();
        for(int i=0; i<4; i++)
        {
            node ext;
            ext.x=now.x+dir[i][0];
            ext.y=now.y+dir[i][1];
            if(ext.x>=1&&ext.x<=3&&ext.y>=1&&ext.y<=3)
            {
                decontor(now.ash);
                swap(seq[(now.x-1)*3+now.y],seq[(ext.x-1)*3+ext.y]);
                int k=contor();
                if(!vis[k])
                {
                    ext.ash=k;
                    ext.path=now.path+ddir[i];
                    vis[k]=1;
                    path[k]=ext.path;
                    qu.push(ext);
                }
            }
        }
    }
}
int main()
{

    bfs();
    char c;
    while(cin>>c)
    {
        if(c=='x')
            seq[1]=9;
        else
            seq[1]=c-'0';
        for(int i=2; i<=9; i++)
        {
            cin>>c;
            if(c=='x')
                seq[i]=9;
            else
                seq[i]=c-'0';
        }
        int k=contor();
        if(vis[k])
        {
            stack<char>s;
            for(int i=0;i<path[k].length();i++)
                s.push(path[k][i]);
            while(!s.empty())
            {
                cout<<s.top();
                s.pop();
            }
            cout<<endl;
        }
        else cout<<"unsolvable"<<endl;
    }
}
//HDU1043