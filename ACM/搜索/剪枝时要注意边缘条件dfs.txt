#include<stdio.h>
#include<string.h>
int continent[25],n,m,k,att[105][3],max1=-1,mn[505],mx=-1;
struct state
{
    int conid,fv;
} a[205];
void dfs(int step)
{
    if(step>k)
        return ;
    if(step>max1)
        max1=step;
    for(int i=0; i<3; i++)
    {
        mx=-1;
        a[att[step][(i+1)%3]].fv+=2;
        a[att[step][(i+2)%3]].fv+=2;
        mn[step]= a[att[step][i]].fv;
        if( a[att[step][i]].fv-2>=1)
            a[att[step][i]].fv-=2;
        else
            a[att[step][i]].fv=1;
        for(int j=0; j<n; j++)
            if((a[j].conid==a[att[step][(i+1)%3]].conid&&j!=att[step][(i+1)%3])||(a[j].conid==a[att[step][(i+2)%3]].conid&&j!=att[step][(i+2)%3]))
                a[j].fv++;
        for(int op=0; op<n; op++)
            if(a[op].fv>mx)
                mx=a[op].fv;
        if(mx<=5)
            dfs(step+1);
        a[att[step][(i+1)%3]].fv-=2;
        a[att[step][(i+2)%3]].fv-=2;
        a[att[step][i]].fv=mn[step];
        for(int j=0; j<n; j++)
            if((a[j].conid==a[att[step][(i+1)%3]].conid&&j!=att[step][(i+1)%3])||(a[j].conid==a[att[step][(i+2)%3]].conid&&j!=att[step][(i+2)%3]))
                a[j].fv--;
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    for(int c=1; c<=t; c++)
    {
        max1=-1;
        scanf("%d%d%d",&n,&m,&k);
        for(int i=0; i<n; i++)
            scanf("%d",&a[i].conid);
        for(int i=0; i<n; i++)
            scanf("%d",&a[i].fv);
        for(int i=0; i<k; i++)
            scanf("%d%d%d",&att[i][0],&att[i][1],&att[i][2]);
        dfs(0);
        printf("Case #%d: %d\n",c,max1);
    }
}

\\ HDU 4536