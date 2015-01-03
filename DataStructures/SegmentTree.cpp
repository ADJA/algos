/*************************************************************************************

    Segment tree. Solves RMQ problem (maximum on a segment and value update)
    O(N) on precalculation, O(logN) on query.

    Based on problem 3309 from informatics.mccme.ru: 
    http://informatics.mccme.ru/moodle/mod/statements/view.php?chapterid=3309

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
const int INF = (int) 1e9;

int n, num, qn;
int a[MAXN];
int tree[4 * MAXN];
int l, r;

int getMax(int l, int r) {
    l = num + l - 1; r = num + r - 1;
    int res = -INF;
    
    while (l <= r) {
        if (l & 1) {
            res = max(res, tree[l]);
            l++;
        }
        if (r % 2 == 0) {
            res = max(res, tree[r]);
            r--;
        }
        l /= 2; r /= 2;
    }

    return res;
}

void update(int pos, int val) {
    pos = num + pos - 1;
    tree[pos] = val;
    pos /= 2;
    while (pos >= 1) {
        tree[pos] = max(tree[pos * 2], tree[pos * 2 + 1]);
        pos /= 2;
    }
}

int main() {
    //assert(freopen("input.txt","r",stdin));
    //assert(freopen("output.txt","w",stdout));

    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    num = 1;
    while (num < n)
        num *= 2;

    for (int i = num; i < 2 * num; i++) {
        if (i - num + 1 <= n)
            tree[i] = a[i - num + 1];
        else
            tree[i] = -INF;
    }
    
    for (int i = num - 1; i >= 1; i--) {
        tree[i] = max(tree[i * 2], tree[i * 2 + 1]);
    }

    scanf("%d", &qn);
    for (int i = 1; i <= qn; i++) {
        scanf("%d %d", &l, &r);
        printf("%d ", getMax(l, r));
    }

    return 0;
}