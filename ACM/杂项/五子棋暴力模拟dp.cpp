#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
char mapp[15][15];
int dp[15][15][7];
int main()
{
    int flag=0;
    for(int i=1; i<=10; i++)
        for(int j=1; j<=10; j++)
            scanf(" %c",&mapp[i][j]);
    for(int l=1; l<=10; l++)
    {
        if(flag==1) break;
        for(int r=1; r<=10; r++)
        {
            if(flag==1) break;
            memset(dp,0,sizeof(dp));
            if(mapp[l][r]=='.')
            {
                if(flag==1) break;
                mapp[l][r]='X';
                for(int i=1; i<=5; i++)
                {
                    if(flag==1) break;
                    for(int j=1; j<=10; j++)
                    {
                        if(flag==1) break;
                        for(int k=1; k<=10; k++)
                        {
                            if(flag==1) break;
                            if(i==1&&mapp[j][k]=='X')
                                dp[j][k][i]=dp[j-1][k][i]+1;
                            else if(i==2&&mapp[j][k]=='X')
                                dp[j][k][i]=dp[j][k-1][i]+1;
                            else if(i==3&&mapp[j][k]=='X')
                                dp[j][k][i]=dp[j-1][k-1][i]+1;
                            else if(i==4&&mapp[j][k]=='X')
                                dp[j][k][i]=dp[j-1][k+1][i]+1;
                            else if(i==5&&mapp[j][k]=='X')
                            {
                                dp[j][k][i]=max(dp[j][k][1],max(dp[j][k][2],max(dp[j][k][3],dp[j][k][4])));
                                if(dp[j][k][i]==5)
                                {
                                    flag=1;
                                    break;
                                }
                            }

                        }
                    }
                }
                mapp[l][r]='.';
            }
        }
    }
    if(flag)
        printf("YES\n");
    else printf("NO\n");
}

\\ codeforces 825B