/*************************************************************************************

	Implicit segment tree with addition on the interval
	and getting the value of some element. 

	Works on the intervals like [1..10^9]. 
	O(logN) on query, O(NlogN) of memory.

	Author: Bekzhan Kassenov.

	Based on problem 3327 from informatics.mccme.ru
	http://informatics.mccme.ru/moodle/mod/statements/view.php?chapterid=3327

*************************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

typedef long long ll;

struct Node {
	ll sum;
	Node *l, *r;

	Node() : sum(0), l(NULL), r(NULL) { }
};

void add(Node *v, int l, int r, int q_l, int q_r, ll val) {
	if (l > r || q_r < l || q_l > r)
		return;

	if (q_l <= l && r <= q_r) {
		v -> sum += val;
		return;
	}

	int mid = (l + r) >> 1;

	if (v -> l == NULL)
		v -> l = new Node();

	if (v -> r == NULL)
		v -> r = new Node();

	add(v -> l, l, mid, q_l, q_r, val);
	add(v -> r, mid + 1, r, q_l, q_r, val);
}

ll get(Node *v, int l, int r, int pos) {
	if (!v || l > r || pos < l || pos > r)
		return 0;

	if (l == r) 
		return v -> sum;

	int mid = (l + r) >> 1;

	return v -> sum + get(v -> l, l, mid, pos) + get(v -> r, mid + 1, r, pos);
}

int n, m, t, x, y, val;
char c;

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	Node *root = new Node();

	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		add(root, 0, n - 1, i, i, x);
	}

	scanf("%d", &m);

	for (int i = 0; i < m; i++) {
		scanf("\n%c", &c);

		if (c == 'a') {
			scanf("%d%d%d", &x, &y, &val);

			add(root, 0, n - 1, --x, --y, val);
		} else {
			scanf("%d", &x);

			printf("%I64d ", get(root, 0, n - 1, --x));
		}
	}

	return 0;
}