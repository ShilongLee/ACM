#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<math.h>
using namespace std;
int w[5005];
int main()
{
    int n,c,sum=0;
    scanf("%d%d",&n,&c);
    for(int i=1;i<=n;i++)
        scanf("%d",&w[i]);
        sort(w+1,w+n+1);
        for(int i=1;i<=n;i++)
            if(c-w[i]>0)
            {
                c-=w[i];
                sum++;
            }
            printf("%d\n",sum);
}
