#include <stdio.h>
typedef long long ll;
const ll N = 3e6 + 5;
ll Inv[N], n, mod;
int main()
{
    scanf("%d%d", &n, &mod);
    Inv[1] = 1;
    for (int i = 2; i <= n; ++i)
        Inv[i] = (ll)(mod - mod / i) * Inv[mod % i] % mod;
    for (int i = 1; i <= n; ++i)
        printf("%lld\n", Inv[i]);
    return 0;
}
//洛谷3811