#include<stdio.h>
#include<algorithm>
#include<string>
#include<string.h>
using namespace std;
int a[505];
int b[505];
int c[505];
void LCS(int n)
{
    for(int i=1; i<=n; i++)
    {
        int k=0,temp=0;
        for(int j=1; j<=n; j++)
        {
            k=temp;
            temp=c[j];
            if(a[j]==b[i])
                c[j]=k+1;
            else
                c[j]=max(c[j],c[j-1]);
        }
    }
}
int main()
{
    int n,x;
    scanf("%d",&n);
    memset(c,0,sizeof(c));
    for(int i=1; i<=n; i++)
    {
        b[i]=i;
        scanf("%d",&x);
        a[x]=i;
    }
    LCS(n);
    printf("%d\n",c[n]);
}
