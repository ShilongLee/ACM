#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<queue>
#include<map>
using namespace std;
char mapp[33];
int ans;
bool check(char a[])
{
    for(int i=0; i<4; i++)
        for(int j=0; j<7; j++)
            if(a[i*8+j]!=(i+1)*10+j+1)
                return false;
    return true;
}
struct node
{
    int step;
    char str[33];
    int dir[4];
};
void bfs(node now)
{
    map<string,int>mp;
    mp[now.str]=1;
    queue<node>qu;
    qu.push(now);
    while(!qu.empty())
    {
        node q1=qu.front();
        qu.pop();
        if(check(q1.str))
        {
            ans=q1.step;
            return;
        }
        for(int i=0; i<4; i++)
        {
            node q2=q1;
            if(q2.str[q2.dir[i]-1]==1||q2.str[q2.dir[i]-1]%10==7)
                continue;
            for(int j=0; j<32; j++)
            {
                if(q2.str[j]==q2.str[q2.dir[i]-1]+1)
                {
                    q2.str[q2.dir[i]]=q2.str[j];
                    q2.str[j]=1;
                    q2.step++;
                    q2.dir[i]=j;
                    break;
                }
            }
            if(mp[q2.str]==1)
                continue;
            else
                mp[q2.str]=1;
            qu.push(q2);
        }
    }
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        node now;
        int k=0,ep=0;
        ans=-1;
        for(int i=1; i<=4; i++)
        {
            mapp[k++]=i*10+1;
            for(int j=1; j<=7; j++)
            {
                int temp;
                scanf("%d",&temp);
                mapp[k]=temp;
                if(temp%10==1)
                {
                    mapp[k]=1;
                    now.dir[ep++]=k;
                }
                k++;
            }

        }
        now.step=0;
        strcpy(now.str,mapp);
        /*for(int i=0; i<32; i++)
            printf("%d ",now.str[i]);
        cout<<endl;
        for(int i=0; i<4; i++)
            cout<<now.dir[i]<<' ';
        cout<<endl;*/
        bfs(now);
        cout<<ans<<endl;
        /*for(int i=0;i<32;i++)
        printf("%d ",now.str[i]);
        printf("\n");*/
    }
    return 0;
}

//hdu1067