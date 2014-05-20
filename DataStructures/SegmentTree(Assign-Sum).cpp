/**********************************************************************
    
	Segment Tree with assignment and sum on the interval
	Can be used in problem D from CFR #200: 
	http://codeforces.ru/contest/343/problem/D

	TODO: find easier problem for this algorithm.

**********************************************************************/

const int MAXN = 105000;
const int zero = -1;

struct node {
	int sum;
	int val;
	int size;
};

int n, x, l, r;
int a[MAXN];
vector <node> tree;

void build (int v, int L, int R, int a[]) {    	
    if ( L == R ) {
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
	if (tree[v].val != zero) {
		if (tree[v].size != 1) {
			tree[2 * v].val = tree[v].val;
			tree[2 * v + 1].val = tree[v].val;
		}
		tree[v].sum = tree[v].size * tree[v].val;
		tree[v].val = zero;
	}
}

void assign(int v, int L, int R, int l, int r, int val) {
	if (l > r) return;
	push(v);
	if (L == l && R == r) {
		tree[v].val = val;
		tree[v].sum = val * tree[v].size;
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

int getsum(int v, int L, int R, int l, int r) {
	if (l > r) return 0;
	push(v);
	if (l == L && r == R) return tree[v].sum;
	int mid = L + (R - L) / 2;
	int res = getsum(2 * v, L, mid, l, min(mid, r)) + getsum(2 * v + 1, mid + 1, R, max(l, mid + 1), r);
	return res;
}

int main() {
	//Reading input
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) 
		scanf("%d", &a[i]);

	//Setting up the segment tree
	tree.resize(4 * n);
	build(1, 1, n, a);

	//Assigning the value x on l, r
	scanf("%d %d %d", &l, &r, &x);
	assign(1, 1, n, l, r, x);

	//Getting the sum on l, r
	scanf("%d %d", &l, &r);
	cout << getsum(1, 1, n, l, r);

	return 0;
}