#include<stdio.h>
#include<algorithm>
#include<iostream>
#include<string.h>
using namespace std;
int t[1005][1005];
int s[1005][1005];
//int weight[1005][1005];
int weight[7][7] = {{0,0,0,0,0,0,0},{0,0,2,2,3,1,4},{0,2,0,1,5,2,3},{0,2,1,0,2,1,4},{0,3,5,2,0,6,2},{0,1,2,1,6,0,1},{0,4,3,4,2,1,0}};//凸多边形的权
int w(int a,int b,int c)
{
    return weight[a][b]+weight[b][c]+weight[a][c];
}
int f(int n)
{
    for(int r=1; r<n; r++)
        for(int i=1; i<=n-r; i++)
        {
            int j=i+r;
            if(r==1)
                t[i][j]=0;
            else if(r==2)
                t[i][j]=w(i,i+1,j);
            else
            {
                t[i][j]=t[i+1][j]+w(i,i+1,j);
            }
            for(int k=i+2; k<j; k++)
                t[i][j]=min(t[i][j],t[i][k]+t[k][j]+w(i,k,j));
        }
}
int main()
{
    /*int n;
    scanf("%d",&n);
    memset(weight,0,sizeof(weight));
    for(int i=1; i<=n; i++)
        for(int j=i+1; j<=n; j++)
        {
            scanf("%d",&weight[i][j]);
            weight[i][j]=weight[j][i];
        }*/
    f(6);
    for(int i=1; i<=6; i++)
    {
        for(int j=1; j<=6; j++)
            printf("%d ",t[i][j]);
        printf("\n");
    }
}
