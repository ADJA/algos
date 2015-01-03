/******************************************************************************

    Hashing in strings based problems.

    This code compares substrings using two hashes (one
    uses 2^64 as a modulo, another 10^9 + 7)   

    Based on problem C from here: http://codeforces.ru/gym/100133

******************************************************************************/

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <cassert>
#include <utility>
#include <iomanip>

using namespace std;

const int MAXN = 105000;
const int mod = (int) 1e9 + 7;
const int p = 53;       

string s;
int n, m;
long long h1[MAXN], h2[MAXN];
long long pp1[MAXN], pp2[MAXN];

long long getHash1(int l, int r) {
    l--; r--;
    long long h = h1[r];
    if (l > 0)
        h -= h1[l - 1];
    h *= pp1[n - 1 - r];
    return h;
}

long long getHash2(int l, int r) {
    l--; r--;
    long long h = h2[r];
    if (l > 0)
        h = (h - h2[l - 1] + mod) % mod;
    h = (h * pp2[n - 1 - r]) % mod;
    return h;
}

int main() {
    assert(freopen("substrcmp.in","r",stdin));
    assert(freopen("substrcmp.out","w",stdout));

    getline(cin, s);
    n = (int) s.length();

    pp1[0] = 1; pp2[0] = 1;
    for (int i = 1; i <= n; i++) {
        pp1[i] = pp1[i - 1] * p;
        pp2[i] = (pp2[i - 1] * p) % mod; 
    }

    h1[0] = s[0] - 'a' + 1;
    h2[0] = (s[0] - 'a' + 1) % mod;
    for (int i = 1; i < n; i++) {
        h1[i] = h1[i - 1] + pp1[i] * (s[i] - 'a' + 1);
        h2[i] = (h2[i - 1] + pp2[i] * (s[i] - 'a' + 1)) % mod; 
    }

    scanf("%d", &m);

    for (int i = 1; i <= m; i++) {
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        if (getHash1(a, b) == getHash1(c, d) && getHash2(a, b) == getHash2(c, d))
            puts("Yes");
        else
            puts("No");
    }

    return 0;
}