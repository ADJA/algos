
// 2014-04-26
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
int maxisum[200000];
int sum[200000];
int maxlsum[200000];
int maxrsum[200000];
int a[50000];
int N;
void set(int node, int val) {
    sum[node] = maxisum[node] = maxlsum[node] = maxrsum[node] = val;
}
void calc(int node) {
    sum[node] = sum[2*node] + sum[2*node+1];
    maxlsum[node] = max(maxlsum[2*node], sum[2*node] + maxlsum[2*node+1]);
    maxrsum[node] = max(maxrsum[2*node+1], sum[2*node+1] + maxrsum[2*node]);
    maxisum[node] = max(max(maxisum[2*node], maxisum[2*node+1]),
                        maxrsum[2*node] + maxlsum[2*node+1]);
}
void build_tree(int node, int l, int r) {
    if (r - l == 1) {
        set(node, a[l]);
    } else {
        int m = l + (r - l + 1)/2;
        build_tree(2*node, l, m);
        build_tree(2*node+1, m, r);
        calc(node);
    }
}
void update(int node, int l, int r, int idx, int newval) {
    if (r - l == 1) {
        a[idx] = newval;
        set(node, newval);
    } else {
        int m = l + (r - l + 1)/2;
        if (idx < m) {
            update(2*node, l, m, idx, newval);
        } else {
            update(2*node+1, m, r, idx, newval);
        }
        calc(node);
    }
}
void query_rec(int node, int tbegin, int tend, int abegin, int aend,
               vector<int>& nodelist) {
    if (tbegin >= abegin && tend <= aend) {
        nodelist.push_back(node);
    } else {
        int mid = tbegin + (tend - tbegin + 1)/2;
        if (mid > abegin && tbegin < aend) {
            query_rec(2*node, tbegin, mid, abegin, aend, nodelist);
        }
        if (tend > abegin && mid < aend) {
            query_rec(2*node+1, mid, tend, abegin, aend, nodelist);
        }
    }
}
int query(int l, int r) {
    vector<int> nodelist;
    query_rec(1, 0, N, l, r, nodelist);
    int res = -2e9;
    int t = -2e9;
    for (int i = 0; i < nodelist.size(); i++) {
        res = max(res, maxisum[nodelist[i]]);
        res = max(res, t + maxlsum[nodelist[i]]);
        t = max(t + sum[nodelist[i]], maxrsum[nodelist[i]]);
    }
    return res;
}
int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", a+i);
    }
    build_tree(1, 0, N);
    int M; scanf("%d", &M);
    while (M--) {
        int op, x, y;
        scanf("%d %d %d", &op, &x, &y);
        if (op == 0) {
            update(1, 0, N, x-1, y);
        } else {
            printf("%d\n", query(x-1, y));
        }
    }
}
