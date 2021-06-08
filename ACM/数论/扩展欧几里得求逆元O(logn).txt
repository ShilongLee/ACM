#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long ll;
ll a, mod;
void Exgcd(ll a, ll b, ll &x, ll &y)
{
    if (!b)
        x = 1, y = 0;
    else
        Exgcd(b, a % b, y, x), y -= a / b * x;
}
ll Inv(ll a, ll mod)
{
    ll x, y;
    Exgcd(a, mod, x, y);
    return (x % mod + mod) % mod;
}
int main()
{
    cin >> a >> mod;
    ll ans = Inv(a, mod);
    cout << ans << endl;
    return 0;
}




//扩展欧几里得   /*   给予二整数 a 与 b, 必存在有整数 x 与 y 使得ax + by = gcd(a,b)      */
                         /*   在这里  a*x+k*mod≡1(mod)   求解出x就是a的逆元   */
//ax+by≡gcd(a,b)
//b=0时 此时x=1,y=0
//设a*x1+b*y1=gcd(a,b)
//有b*x2+(a%b)*y2=gcd(b,a%b)
//由于gcd(a,b)=gcd(b,a%b)
//那么a*x1+b*y1=b*x2+(a%b)*y2
//即a*x1+b*y1=b*x2+(a-a/b*b)*y2=a*y2+b*x2-a/b*b*y2
//也就是a*x1+b*y1==a*y2+b*(x2-a/b*y2)

//重点
//根据恒等可得 x1=y2;
//            y1=x2-a/b*y2；
//x1 y1为第一层
//x2 y2为第二层
//这样就得出了相应层数之间的关系
//最后一层xn yn
//传到上一层后是yn xn
//所以处理后 上一层是 yn xn-a/b*yn  转换到当前层编号就是x     y-a/b*x
//所以得出if(!b) x=1,b=0                                       |
//else Exgcd(b,a%b,y,x),y-=a/b*x;------------------------------