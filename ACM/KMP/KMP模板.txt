#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
using namespace std;

const int LEN = 105;
int ext[LEN];      //ext数组
char target[LEN];  //目标串
char pattern[LEN]; //模式串
int len_target, len_pattern;

void get_ext()
{
    int j = 0, k = -1;
    ext[0] = -1;
    while (j < len_pattern)
    {
        if (k == -1 || pattern[j] == pattern[k])
        {
            ++j, ++k;
            if (pattern[j] == pattern[k])
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
    int i = 0, j = 0;
    while (i < len_target && j < len_pattern)
    {
        if (j == -1 || target[i] == pattern[j])
            ++i, ++j;
        else
            j = ext[j];
    }
    if (j == len_pattern)
        return i - j;
    else
        return -1;
}

int main()
{
    cin >> target;
    cin >> pattern;
    len_target = strlen(target);
    len_pattern = strlen(pattern);
    get_ext();
    int ans = KMP();
    cout << ans << endl;
}