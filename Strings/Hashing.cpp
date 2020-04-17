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

class Hashing {
private:
    const int mod = (int) 1e9 + 7;
    const int p = 53; // should be prime
    string s;
    int n;
    vector<long long> h1, h2;
    vector<long long> p1, p2;
public:
    void init(string st) {
        s = st;
        n = (int) s.length();

        p1.assign(n + 1, 1); 
        p2.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            p1[i] = p1[i - 1] * p;
            p2[i] = p2[i - 1] * p % mod; 
        }

        char minChar = s[0];
        for (int i = 0; i < n; i++) minChar = min(minChar, s[i]);

        h1.assign(n, 0); 
        h2.assign(n, 0);
        h1[0] = s[0] - minChar + 1;
        h2[0] = (s[0] - minChar + 1) % mod;
        for (int i = 1; i < n; i++) {
            h1[i] = h1[i - 1] + p1[i] * (s[i] - minChar + 1);
            h2[i] = (h2[i - 1] + p2[i] * (s[i] - minChar + 1)) % mod; 
        }
    }
    long long getHash1(int l, int r) {
        long long h = h1[r];
        if (l > 0)
            h -= h1[l - 1];
        h *= p1[n - 1 - r];
        return h;
    }
    long long getHash2(int l, int r) {
        long long h = h2[r];
        if (l > 0)
            h = (h - h2[l - 1] + mod) % mod;
        h = h * p2[n - 1 - r] % mod;
        return h;
    }
    pair<long long, long long> getHash(int l, int r) {
        return {getHash1(l, r), getHash2(l, r)};
    }
};

string s;
int n, m;

int main() {
    assert(freopen("substrcmp.in","r",stdin));
    assert(freopen("substrcmp.out","w",stdout));

    getline(cin, s);
    n = (int) s.length();

    Hashing hashing;
    hashing.init(s);

    scanf("%d", &m);

    for (int i = 1; i <= m; i++) {
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        a--; b--; c--; d--;
        if (hashing.getHash(a, b) == hashing.getHash(c, d))
            puts("Yes");
        else
            puts("No");
    }

    return 0;
}
