#include<stdio.h>
#include<algorithm>
#include<math.h>
#include<string.h>
using namespace std;
struct Ma
{
    int m,n;
} a[1005];
int s[1005][1005];
int m[1005][1005];
void Mach(int n)
{
    for(int r=1; r<n; r++)
    {
        for(int i=0; i<n-r+1; i++)
        {
            int j=i+r;
            m[i][j]=m[i+1][j]+a[i].m*a[i+1].m*a[j].n;
            s[i][j]=i;
            for(int k=i+1; k<j; k++)
            {
                if((m[i][k]+m[k+1][j]+a[i].m*a[k+1].m*a[j].n)<m[i][j])
                {
                    m[i][j]=m[i][k]+m[k+1][j]+a[i].m*a[k+1].m*a[j].n;
                    s[i][j]=k;
                }
            }
        }
    }
}
int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        memset(m,0,sizeof(m));
        memset(s,0,sizeof(s));
        for(int i=0; i<n; i++)
            scanf("%d%d",&a[i].m,&a[i].n);
        Mach(n);
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
                printf("%d ",m[i][j]);
            printf("\n");
        }
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
                printf("%d ",s[i][j]);
            printf("\n");
        }
    }
}
