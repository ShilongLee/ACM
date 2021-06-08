#include<stdio.h>
#include<algorithm>
using namespace std;
class jobtype
{
public:
    bool operator<=(jobtype a) const
    {
        return key<=a.key;
    }
    int key,job,index;
} d[505];
int a[505];
int b[505];
int c[505];
void BubbleSort(jobtype *d,int n)
{
    int i,j,flag;
    jobtype temp;

    for(i=0; i<n; i++)
    {
        flag = 0;
        for(j=n-1; j>i; j--)
        {
            if(d[j]<=d[j-1])
            {
                temp = d[j];
                d[j] = d[j-1];
                d[j-1] = temp;
                flag = 1;
            }
        }
        if(flag == 0)
        {
            break;
        }
    }
}
int FS(int n)
{
    for(int i=0; i<n; i++)
    {
        d[i].key=a[i]>b[i]?b[i]:a[i];
        d[i].job=a[i]<=b[i];
        d[i].index=i;
    }
    BubbleSort(d,n);
    int j=0,k=n-1;
    for(int i=0; i<n; i++)
    {
        if(d[i].job)
            c[j++]=d[i].index;
        else
            c[k--]=d[i].index;
    }
    j=a[c[0]];
    k=b[c[0]];
    for(int i=1; i<n; i++)
    {
        j+=a[c[i]];
        k=j<k?k+b[c[i]]:j+b[c[i]];
    }
    return k;
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0; i<n; i++)
        scanf("%d%d",&a[i],&b[i]);
    printf("%d\n",FS(n));
    for(int i=0; i<n; i++)
        printf("%d ",c[i]);
    printf("\n");
}
