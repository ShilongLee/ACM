#include<stdio.h>
#include<algorithm>
#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<time.h>
using namespace std;
#define random(a,b) (rand()%(b-a+1)+a)
struct point
{
    double x,y;
} s[10000005];
bool cmpx(point a,point b)
{
    return a.x<b.x;
}
bool cmpy(point a,point b)
{
    return a.y<b.y;
}
double dis(point a,point b)
{
    return sqrt((b.y-a.y)*(b.y-a.y)+(a.x-b.x)*(a.x-b.x));
}
double abs(double a)
{
    return a>0?a:-a;
}
double cpair(point s[],int l,int r)
{
    if(r-l==1) return dis(s[r],s[l]);
    if(r-l==2) return min(dis(s[l],s[l+1]),min(dis(s[l+1],s[r]),dis(s[l],s[r])));
    int m=(l+r)/2;
    double d1=cpair(s,l,m),d2=cpair(s,m+1,r);
    double d=min(d1,d2);
    int left=l,right=r;
    while(s[left].x<s[m].x-d&&left<m)
        left++;
    while(s[right].x>s[m].x+d&&right>m)
        right--;
    sort(s+left,s+m+1,cmpy);
    sort(s+m,s+right+1,cmpy);
    for(int i=left; i<=m; i++)
        for(int j=m+1; j<=right; j++)
        {
            if(abs(s[i].y-s[j].y)>=d)
                break;
            else
            {
                if(dis(s[i],s[j])<d)
                    d=dis(s[i],s[j]);
            }
        }
    return d;
}
int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        srand(int(time(0)));
        for(int i=1;i<=n;i++)
        {
            s[i].x=random(100,1000)*0.01;
            s[i].y=random(100,1000)*0.01;
        }
        /*for(int i=1; i<=n; i++)
            scanf("%lf%lf",&s[i].x,&s[i].y);*/
        sort(s+1,s+n+1,cmpx);
        for(int i=1; i<=n; i++)
        {
            printf("%.2lf %.2lf\n",s[i].x,s[i].y);
        }
        cout<<cpair(s,1,n)<<endl;
    }
}
