/*************************************************************************************

    Fenwick tree for sum on the interval and update of an element.  
    O(logN) on operation.

    Based on problem 3317 from informatics.mccme.ru: 
    http://informatics.mccme.ru/moodle/mod/statements/view.php?chapterid=3317#1

*************************************************************************************/

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

int n, m;
int a[MAXN];
long long f[MAXN];
char q;
int l, r;

void update(int pos, int delta) {
    for (; pos <= n; pos = (pos | (pos + 1)))
        f[pos] += delta;
}

long long sum(int pos) {
    long long res = 0;
    for (; pos > 0; pos = (pos & (pos + 1)) - 1)
        res += f[pos];
    return res;
}

long long sum(int l, int r) {
    return sum(r) - sum(l - 1);
}

int main() {
    //assert(freopen("input.txt","r",stdin));
    //assert(freopen("output.txt","w",stdout));

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        update(i, a[i]);
    }

    scanf("%d\n", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%c %d %d\n", &q, &l, &r);
        if (q == 's') {
            cout << sum(l, r) << " ";
        }
        else {
            int delta = r - a[l];
            a[l] = r;
            update(l, delta);
        } 
    } 

    return 0;
}
