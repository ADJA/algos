/************************************************************************************

	Heavy-light decomposition with segment trees in paths.
	Used for finding maximum on the path between two vertices.
	O(N) on building, O(logN ^ 2) on query. 

	Based on problem 1553 from acm.timus.ru 
	http://acm.timus.ru/problem.aspx?space=1&num=1553

************************************************************************************/

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

struct SegmentTree {
	int * tree;
	int size;

	void init(int sz) {
		tree = new int[4 * sz];
		memset(tree, 0, 4 * sz * sizeof(int));
		size = sz;
	}

	int getMax(int v, int from, int to, int l, int r) {
		if (l > to || r < from)
			return 0;
		if (from == l && to == r)
			return tree[v];
		int mid = (from + to) / 2;
		int res = getMax(v * 2, from, mid, l, min(r, mid));
		res = max(res, getMax(v * 2 + 1, mid + 1, to, max(l, mid + 1), r));
		return res;
	}

	int getMax(int l, int r) {
		return getMax(1, 1, size, l, r); 
	}

	void update(int v, int from, int to, int pos, int val) {
		if (pos > to || pos < from)
			return;
		if (from == pos && to == pos) {
			tree[v] = val;
			return;
		}
		int mid = (from + to) / 2;
		update(v * 2, from, mid, pos, val);
		update(v * 2 + 1, mid + 1,  to, pos, val);
		tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
	}

	void update(int pos, int val) {
		update(1, 1, size, pos, val);
	}
};

int n, qn;
char q;
int a, b;
int timer;
int sz[MAXN];
int tin[MAXN], tout[MAXN];    
int val[MAXN];
vector <int> g[MAXN];
int p[MAXN];
int chain[MAXN], chainRoot[MAXN];
int chainSize[MAXN], chainPos[MAXN];
int chainNum;
SegmentTree tree[MAXN];

bool isHeavy(int from, int to) {
	return sz[to] * 2 >= sz[from];
}

void dfs(int v, int par = -1) {
	timer++;
	tin[v] = timer;
	p[v] = par;
	sz[v] = 1;

	for (int i = 0; i < (int) g[v].size(); i++) {
		int to = g[v][i];
		if (to == par)
			continue;
		dfs(to, v);
		sz[v] += sz[to];
	}

	timer++;
	tout[v] = timer;
}

int newChain(int root) {
	chainNum++;
	chainRoot[chainNum] = root;
	return chainNum;
}

void buildHLD(int v, int curChain) {
	chain[v] = curChain;
	chainSize[curChain]++;
	chainPos[v] = chainSize[curChain];

	for (int i = 0; i < g[v].size(); i++) {
		int to = g[v][i];
		if (p[v] == to)
			continue;
		if (isHeavy(v, to))
			buildHLD(to, curChain);
		else
			buildHLD(to, newChain(to));
	}	
}

bool isParent(int a, int b) {
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int getMax(int a, int b) {
	int res = 0;
	while (true) {
		int curChain = chain[a];
		if (isParent(chainRoot[curChain], b))
			break;
		res = max(res, tree[curChain].getMax(1, chainPos[a]));
		a = p[chainRoot[curChain]];
	}
	while (true) {
		int curChain = chain[b];
		if (isParent(chainRoot[curChain], a))
			break;                                          
		res = max(res, tree[curChain].getMax(1, chainPos[b]));
		b = p[chainRoot[curChain]];
	}
	int from = chainPos[a], to = chainPos[b];
	if (from > to)
		swap(from, to);
	res = max(res, tree[chain[a]].getMax(from, to));
	return res;
}


int main() {
	//assert(freopen("input.txt","r",stdin));
	//assert(freopen("output.txt","w",stdout));

	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int from, to;
		scanf("%d %d", &from, &to);
		g[from].push_back(to);
		g[to].push_back(from);
	}

	dfs(1);
	buildHLD(1, newChain(1));

	for (int i = 1; i <= chainNum; i++) {
		tree[i].init(chainSize[i]);	
	}

	scanf("%d\n", &qn);
	for (int i = 1; i <= qn; i++) {
		scanf("%c %d %d\n", &q, &a, &b);
		if (q == 'I') {
			val[a] += b;
			tree[chain[a]].update(chainPos[a], val[a]);
		}
		else {
			printf("%d\n", getMax(a, b));
		}
	}    

	return 0;
}