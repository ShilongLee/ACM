#include<stdio.h>
#include<iostream>
#include<string>
#include<string.h>
#include<algorithm>
#include<stack>
using namespace std;
int n,b[5050];
stack<int>c;
int main()
{
    while(~scanf("%d",&n)&&n)
    {
        while(~scanf("%d",&b[1])&&b[1])
        {
            for(int i=2; i<=n; i++)
                scanf("%d",&b[i]);
            int pos=1,k=1;
            while(k<=n)
            {
                c.push(k);
                while(!c.empty()&&c.top()==b[pos])
                {
                    c.pop();
                    pos++;
                }
                k++;
            }
            if(c.empty())
                printf("Yes\n");
            else
                printf("No\n");
            while(!c.empty())
                c.pop();
        }
        printf("\n");
    }
}

//ZOJ 1259