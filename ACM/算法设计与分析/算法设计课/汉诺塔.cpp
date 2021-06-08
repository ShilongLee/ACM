#include<stdio.h>
#include<iostream>
int sum=0;
void h(int n,char a,char b,char c)
{
    if(n==1)
    {
        printf("%c--->%c\n",a,c);
        sum++;
    }
    else
    {
        h(n-1,a,c,b);
        printf("%c--->%c\n",a,c);
        sum++;
        h(n-1,b,a,c);
    }
}
int main()
{
    h(3,'a','b','c');
    printf("%d\n",sum);
}
