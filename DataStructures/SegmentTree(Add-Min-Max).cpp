/******************************************************************************

    Segment Tree with addition and min/max on the interval

    Based on problem 1263E from https://codeforces.com/contest/1263/problem/E

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

const int MAXN = 1000 * 1000 + 100;
const int INF = (int) 1e9;

struct node {
    int mx, mn;
    int add;
};

int n;
int val[MAXN];
string s;
int pos;
node tree[4 * MAXN];

void add(int v, int L, int R, int l, int r, int val) {
    if (l > r) 
        return;
    if (L == l && R == r) {
        tree[v].add += val;
    } else {
        int mid = L + (R - L) / 2;
        add(2 * v + 1, L, mid, l, min(mid, r), val);
        add(2 * v + 2, mid + 1, R, max(mid + 1, l), r, val);
        tree[v].mx = max(tree[2 * v + 1].mx + tree[2 * v + 1].add, tree[2 * v + 2].mx + tree[2 * v + 2].add);
        tree[v].mn = min(tree[2 * v + 1].mn + tree[2 * v + 1].add, tree[2 * v + 2].mn + tree[2 * v + 2].add);
    }
}

int getMin(int v, int L, int R, int l, int r) {
    if (l > r) {
        return INF;
    }
    if (L == l && R == r) {
        return tree[v].mn + tree[v].add;
    }
    int mid = L + (R - L) / 2;
    return tree[v].add + min(getMin(2 * v + 1, L, mid, l, min(mid, r)), getMin(2 * v + 2, mid + 1, R, max(l, mid + 1), r));
}

int getMax(int v, int L, int R, int l, int r) {
    if (l > r) {
        return -INF;
    }
    if (L == l && R == r) {
        return tree[v].mx + tree[v].add;
    }
    int mid = L + (R - L) / 2;
    return tree[v].add + max(getMax(2 * v + 1, L, mid, l, min(mid, r)), getMax(2 * v + 2, mid + 1, R, max(l, mid + 1), r));
}

int main() {
    //assert(freopen("input.txt","r",stdin));
    //assert(freopen("output.txt","w",stdout));  

    scanf("%d\n", &n);
    getline(cin, s);
    pos = 0;

    for (int i = 0; i < (int) s.length(); i++) {
        if (s[i] == 'L') {
            if (pos > 0) pos--;
        } else if (s[i] == 'R') {
            pos++;
        } else {
            int newVal = 0;
            if (s[i] == '(') {
                newVal = 1;
            } else if (s[i] == ')') {
                newVal = -1;
            }
            int delta = newVal - val[pos];
            val[pos] = newVal;
            add(0, 0, n - 1, pos, n - 1, delta);
        }
        int mn = getMin(0, 0, n - 1, 0, n - 1);
        int lastVal = getMin(0, 0, n - 1, n - 1, n - 1);
        if (mn < 0 || lastVal != 0) {
            printf("%d ", -1);
        } else {
            printf("%d ", getMax(0, 0, n - 1, 0, n - 1));
        }
    }

    cout << endl;

    return 0;
}