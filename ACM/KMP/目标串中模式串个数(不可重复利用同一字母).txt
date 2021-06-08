#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
using namespace std;
const int LEN = 1005;
string s1, s2;
int len1, len2;
int ext[LEN];
void get_ext()
{
    ext[0] = -1;
    int j = 0, k = -1;
    while (j < len2)
    {
        if (k == -1 || s2[j] == s2[k])
        {
            if (s2[++j] == s2[++k])
                ext[j] = ext[k];
            else
                ext[j] = k;
        }
        else
            k = ext[k];
    }
}
int KMP()
{
    int res = 0;
    int i = 0, j = 0;
    while (i < len1)
    {
        if (j == -1 || s1[i] == s2[j])
            ++i, ++j;
        else
            j = ext[j];
        if (j == len2)
        {
            ++res;
            j = 0;
        }
    }
    return res;
}
int main()
{
    while (cin >> s1 && s1 != "#")
    {
        cin >> s2;
        len1 = s1.length();
        len2 = s2.length();
        get_ext();
        cout << KMP() << endl;
    }
    return 0;
}
//hdu2087