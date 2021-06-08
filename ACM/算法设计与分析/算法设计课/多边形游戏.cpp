#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string.h>
#include<math.h>
using namespace std;
int m[105][105][5];
int v[105];
char p[105];
int minf=0,maxf=0;
int n;
void MINFMAXF(int i,int s,int j)
{
    int a=m[i][s][0];
    int b=m[i][s][1];
    int r=(i+s-1)%n+1;
    int c=m[r][j-s][0];
    int d=m[r][j-s][1];
    if(p[r-1]=='+')
    {
        minf=a+c;
        maxf=b+d;
    }
    else
    {
        maxf=max(a*c,max(a*d,max(b*c,b*d)));
        minf=min(a*c,min(a*d,min(b*c,b*d)));
    }
}
int pm()
{
    for(int j=2; j<=n; j++)
        for(int i=1; i<=n; i++)
            for(int s=1; s<j; s++)
            {
                MINFMAXF(i,s,j);
                if(m[i][j][1]<maxf)
                    m[i][j][1]=maxf;
                if(m[i][j][0]>minf)
                    m[i][j][0]=minf;
            }
    int temp=m[1][n][1];
    for(int i=2; i<=n; i++)
        temp=max(temp,m[i][n][1]);
    return temp;
}
int main()
{
    scanf("%d",&n);
    for(int i=1; i<=n; i++)
    {
        scanf("%d",&v[i]);
        m[i][1][0]=v[i];
        m[i][1][1]=v[i];
    }
    for(int i=1; i<=n; i++)
    scanf(" %c",&p[i]);
    printf("%d\n",pm());
}
