#include<iostream>
#include<string.h>
#include<queue>
#include<stack>
#include<stdio.h>
using namespace std;
int status[105][105];//记录状态是否搜索过
int a,b,c;//杯的容量和目的容量
int ok=0;//是否可以到达目的容量
int sum=0;//操作次数
stack<int>path;//路径倒序入栈
struct node
{
    int x,y;
};//状态节点
struct xy
{
    int x,y;
    int staus;
} pathmapp[105][105];//记录状态和父节点，以便回溯出路径。
void bfs(node start)//start为初始节点
{
    queue<node>qu;
    qu.push(start);
    while(!qu.empty())//qu为bfs队列
    {
        node now=qu.front();
        qu.pop();
        //cout<<now.x<<' '<<now.y<<endl;
        if(now.x==c||now.y==c)
        {
            ok=1;
            int x=now.x,y=now.y;
            while(x*x+y*y)
            {
                sum++;
                path.push(pathmapp[x][y].staus);
                int o=x,k=y;
                x=pathmapp[o][k].x;
                y=pathmapp[o][k].y;
            }
            return;
        }
        for(int i=1; i<=6; i++)
        {
            node ext;
            if(i==1)//装满a
            {
                ext.y=now.y;
                ext.x=a;
            }
            else if(i==2)//装满b
            {
                ext.x=now.x;
                ext.y=b;
            }
            else if(i==3)//倒掉a
            {
                ext.x=0;
                ext.y=now.y;
            }
            else if(i==4)//倒掉b
            {
                ext.y=0;
                ext.x=now.x;
            }
            else if(i==5)//a-->b
            {
                ext.x=now.x-(b-now.y);
                if(ext.x<0) ext.x=0;
                ext.y=now.y+now.x;
                if(ext.y>b) ext.y=b;
            }
            else if(i==6)//b-->a
            {
                ext.y=now.y-(a-now.x);
                if(ext.y<0) ext.y=0;
                ext.x=now.x+now.y;
                if(ext.x>a) ext.x=a;
            }
            if(status[ext.x][ext.y])
                continue;
            status[ext.x][ext.y]=1;//状态标记
            pathmapp[ext.x][ext.y].staus=i;//状态记录
            pathmapp[ext.x][ext.y].x=now.x;//记录父节点
            pathmapp[ext.x][ext.y].y=now.y;
            qu.push(ext);
        }
    }
}
int main()
{
    cin>>a>>b>>c;
    memset(status,0,sizeof(status));
    status[0][0]=1;//初始点状态为1
    node start;
    start.x=0;
    start.y=0;
    bfs(start);
    if(sum)
    cout<<sum<<endl;
    while(!path.empty())//栈中节点就是路径
    {
        int s=path.top();
        if(s==1) printf("FILL(1)\n");
        else if(s==2) printf("FILL(2)\n");
        else if(s==3) printf("DROP(1)\n");
        else if(s==4) printf("DROP(2)\n");
        else if(s==5) printf("POUR(1,2)\n");
        else if(s==6) printf("POUR(2,1)\n");
        path.pop();
    }
    if(!ok)
        cout<<"impossible"<<endl;
}

//POJ3414