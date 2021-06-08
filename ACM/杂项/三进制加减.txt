#include<stdio.h>
#include<string.h>
int a[100005];
int b[100005];
int c[100005];
int pow(int x,int p)
{
    int sum=1;
    for(int i=1; i<=p; i++)
        sum*=x;
    return sum;
}
int trans(int x)
{
    int n=0;
    while(x)
    {
        a[n]=x%3;
        x=x/3;
        n++;
    }
    return n;
}
int main()
{
    int m;
    while(~scanf("%d",&m))
    {
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        memset(c,0,sizeof(c));
        int A=0,B=0;
        int l=trans(m);
        for(int i=0; i<l; i++)
        {
            if(a[i]==1)
            {
                b[A]=pow(3,i);
                A++;
            }
            else if(a[i]==2)
            {
                a[i+1]++;
                c[B]=pow(3,i);
                B++;
                if(i==l-1) l++;
            }
            else if(a[i]==3)
            {
                a[i]=0;
                a[i+1]++;
                if(i==l-1) l++;
            }
        }
        printf("%d",B);
        for(int i=0;i<B;i++)
            printf(" %d",c[i]);
        printf("\n%d",A);
        for(int i=0;i<A;i++)
            printf(" %d",b[i]);
        printf("\n");
    }
}

\\HUD 3029