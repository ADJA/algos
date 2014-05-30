/**********************************************************************

	Segment Tree with assignment and sum on the interval

	Based on problem C from http://codeforces.ru/gym/100093

**********************************************************************/

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
const int zero = -1;

struct node {
	long long sum;
	int val;
	int size;
};

int n, m;
char qt; 
int x, l, r;
int a[MAXN];
vector <node> tree;

void build (int v, int L, int R, int a[]) {    	
	if (L == R) {
		tree[v].sum = tree[v].val = a[L];
		tree[v].size = 1;
	}
	else {
		int mid = L + (R - L) / 2;
		build(2 * v, L, mid, a);
		build(2 * v + 1, mid + 1, R, a);
		tree[v].sum = tree[2 * v].sum + tree[2 * v + 1].sum;
		tree[v].val = zero;
		tree[v].size = tree[2 * v + 1].size + tree[2 * v].size;
	}
}

void push(int v) {
	if (tree[v].val == zero)
		return;
	if (tree[v].size != 1) {
		tree[2 * v].val = tree[v].val;
		tree[2 * v + 1].val = tree[v].val;
	}
	tree[v].sum = 1ll * tree[v].size * tree[v].val;
	tree[v].val = zero;
}

void assign(int v, int L, int R, int l, int r, int val) {
	if (l > r) 
		return;
	push(v);
	if (L == l && R == r) {
		tree[v].val = val;
		tree[v].sum = 1ll * val * tree[v].size;
	} else {
		int mid = L + (R - L) / 2;
		assign(2 * v, L, mid, l, min(mid, r), val);
		assign(2 * v + 1, mid + 1, R, max(mid + 1, l), r, val);
		push(2 * v);
		push(2 * v + 1);
		tree[v].sum = tree[2 * v].sum + tree[2 * v + 1].sum;
	}
	push(v);
}

long long getsum(int v, int L, int R, int l, int r) {
	if (l > r) 
		return 0;
	push(v);
	if (l == L && r == R) 
		return tree[v].sum;
	int mid = L + (R - L) / 2;
	long long res = getsum(2 * v, L, mid, l, min(mid, r)) + getsum(2 * v + 1, mid + 1, R, max(l, mid + 1), r);
	return res;
}

int main() {
	assert(freopen("sum.in","r",stdin));
	assert(freopen("sum.out","w",stdout));

	scanf("%d %d\n", &n, &m);

	tree.resize(4 * n);
	build(1, 1, n, a);

	for (int i = 1; i <= m; i++) {
		scanf("%c", &qt);
		if (qt == 'A') {
			scanf("%d %d %d\n", &l, &r, &x);
			assign(1, 1, n, l, r, x);
		}
		else {
			scanf("%d %d\n", &l, &r);
			cout << getsum(1, 1, n, l, r) << endl;
		}
	}
	
	return 0;
}