#include <iostream>
using namespace std;
long long n, mod;
long long pow(long long a, long long b)
{
    long long ans = 1;
    while (b)
    {
        if (b % 2)
            ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}
int main()
{
    cin >> n >> mod; /* 题意：输出n的逆元（同余mod）*/
    cout << pow(n % mod, mod - 2) << endl;
    return 0;
}
//费马小定理 n与mod互质(且mod为质数) n的mod-1次幂≡1即 n^(mod-1)≡1
//提出来个n  n * n^(mod-2)≡1
//所以n的逆元为n^(mod-2)
//用快速幂解决即可
