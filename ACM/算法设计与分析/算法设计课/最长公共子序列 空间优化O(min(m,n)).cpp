#include<stdio.h>
#include<algorithm>
#include<math.h>
#include<string.h>
using namespace std;
int mapp[1005];
char a[1005];
char b[1005];
char c[1005];
void dpmapp(int m,int n)
{

    for(int i=1; i<=m; i++)
    {
        int k=0,pre=0;
        for(int j=1; j<=n; j++)
        {
            k=pre;
            pre=mapp[j];
            if(a[i]==b[j])
                mapp[j]=k+1;
            else
                mapp[j]=max(mapp[j],mapp[j-1]);
        }
    }
}
int main()
{
    while(~scanf("%s%s",a+1,b+1))
    {
        memset(mapp,0,sizeof(mapp));
        int m=strlen(a+1);
        int n=strlen(b+1) ;
        if(m<n)
        {
            strcpy(a+1,c+1);
            strcpy(b+1,a+1);
            strcpy(c+1,b+1);
        }
        dpmapp(max(m,n),min(m,n));
            for(int j=1; j<=n; j++)
                printf("%d ",mapp[j]);
        printf("\n");
    }
}
