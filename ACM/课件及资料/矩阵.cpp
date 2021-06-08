#include <iostream> ///poj 3070 Fibonacci
using namespace std;
const int mod=10000;
int n;
struct Matrix
{
    int m[2][2];
};
Matrix E,p;   ///单位阵E，递推阵p；
Matrix mul(Matrix a,Matrix b) //矩阵乘法
{
    Matrix c;
    for(int i=0;i<2/*a的行数*/;i++)
        for(int j=0;j<2/*b的列数*/;j++)
        {
            c.m[i][j]=0;
            for(int k=0;k<2/*b的行数（或a的列数）*/;k++)c.m[i][j]+=a.m[i][k]*b.m[k][j];
            c.m[i][j]%=mod;
        }
    return c;
}
void get_Matrix_p()  ///递推阵赋值
{
    p.m[0][0]=1;
    p.m[0][1]=1;
    p.m[1][0]=1;
    p.m[1][1]=0;
}
void get_Matrix_E()   ///单位阵赋值
{
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            E.m[i][j]=(i==j);
}
Matrix power(int b) ///矩阵快速幂
{
    Matrix a=p,ans=E;
    while (b) {
        if(b&1)
        {
            ans=mul(ans,a);
            b--;
        }
        b/=2;
        a=mul(a,a);
    }
    return ans;
}
int main()
{
    while (cin>>n,n!=-1)
    {
        get_Matrix_E();
        get_Matrix_p();
        if(n==0)
        {
            cout<<"0"<<endl;
            continue;
        }
        p=power(n-1);
        cout<<p.m[0][0]<<endl;
    }
    return 0;
}
