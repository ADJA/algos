/*************************************************************************************

	Cartesian tree using implicit keys. Implementation below contains
	array segment reverse and finding range minimum. O(logN) on operation.

	Based on problem 111240 from informatics.mccme.ru: 
	http://informatics.mccme.ru/mod/statements/view3.php?chapterid=111240

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
#include <utility>
#include <cstring>
#include <iomanip>

using namespace std;

const int INF = 2 * 1000 * 1000 * 1000;

struct node {
	int y, val;
	int sz, mn;
	bool rev;
	node *l, *r;
	node (int new_val, int new_y) {
		y = new_y; val = new_val; 
		sz = 1; mn = val;
		rev = false;
		l = NULL; r = NULL;
	}
};

typedef node * pnode;

int getsize(pnode t) {
	if (t == NULL)
		return 0;
	return t->sz;
}

int getmin(pnode t) {
	if (t == NULL) 
		return INF;
	return t->mn;
}

void update(pnode t) {
	if (t == NULL) 
		return;
	t->sz = getsize(t->l) + 1 + getsize(t->r);
	t->mn = min(t->val, min(getmin(t->r), getmin(t->l)));
}

void push(pnode t) {
	if (t && t->rev) {
		swap(t->l, t->r);
		if (t->l) 
			t->l->rev ^= true;
		if (t->r)
			t->r->rev ^= true;
		t->rev = false;
	}
}

void merge(pnode &t, pnode l, pnode r) {
	push(l); push(r);
	if (l == NULL) 
		t = r;
	else if (r == NULL) 
		t = l;
	else if (l->y > r->y) {
		merge(l->r, l->r, r); 
		t = l;
	}
	else {
		merge(r->l, l, r->l); 
		t = r;
	}
	update(t);
}

void split(pnode t, pnode &l, pnode &r, int x, int add = 0) {
	push(t);
	if (t == NULL) {
		l = r = NULL;
		return;
	}
	int key = getsize(t->l) + 1 + add;
	if (x <= key) {
		split(t->l, l, t->l, x, add); 
		r = t;
	}
	else {
		split(t->r, t->r, r, x, add + getsize(t->l) + 1); 
		l = t;
	}
	update(t);
}

void reverse(pnode t, int l, int r) {
	pnode a, b;
	split(t, t, a, l, 0);
	split(a, a, b, r - l + 2, 0);
	a->rev ^= true;
	merge(t, t, a);
	merge(t, t, b);
}

int getmin(pnode t, int l, int r) {
	int ans;
	pnode a, b;
	split(t, t, a, l, 0);
	split(a, a, b, r - l + 2, 0);
	ans = getmin(a);
	merge(t, t, a);
	merge(t, t, b);
	return ans;
}

int n, m;
int qt, l, r;
pnode root = NULL, add;

int main() {
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);

	scanf("%d %d\n", &n, &m);
	for (int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		add = new node(x, rand());   
		merge(root, root, add);
	}      

	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d",&qt, &l, &r);
		if (qt == 1) {
			reverse(root, l, r);
		}
		else {
			printf("%d\n", getmin(root, l, r));
		}
	}

	return 0;
}