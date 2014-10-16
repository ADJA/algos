/************************************************************************************

	Finding LCA (Least common ancestor) of two vertices in the tree.
	Uses heavy-light decomposition. 
	O(N) for preprocessing,	O(logN) on query.

	Based on problem 111796 from informatics.mccme.ru 
	http://informatics.mccme.ru/moodle/mod/statements/view.php?chapterid=111796

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

int n, qn;
vector <int> g[MAXN];   
int tin[MAXN], tout[MAXN];
int p[MAXN];
int sz[MAXN];
int chain[MAXN], chainRoot[MAXN]; 
int chainNum;
int timer;

int a[2 * MAXN];
int x, y, z;

long long ans;

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

bool isHeavy(int from, int to) {
	return 2 * sz[to] >= sz[from];
}

int newChain(int root) {
	chainNum++;
	chainRoot[chainNum] = root;
	return chainNum;
}

void buildHLD(int v, int curChain) {
	chain[v] = curChain;
	for (int i = 0; i < g[v].size(); i++) {
		int to = g[v][i];
		if (to == p[v])
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

int lca(int a, int b) {
	while (true) {
		int curChain = chain[a];
		if (isParent(chainRoot[curChain], b))
			break;
		a = p[chainRoot[curChain]];	
	}
	while (true) {
		int curChain = chain[b];
		if (isParent(chainRoot[curChain], a))
			break;
		b = p[chainRoot[curChain]];
	}
	if (isParent(a, b))
		return a;
	else
		return b;
}

int main() {
	//assert(freopen("input.txt","r",stdin));
	//assert(freopen("output.txt","w",stdout));  

	scanf("%d %d", &n, &qn);

	for (int i = 1; i < n; i++) {
		int par;
		scanf("%d", &par);
		par++;
		g[i + 1].push_back(par);
		g[par].push_back(i + 1);
	}

	dfs(1);
	buildHLD(1, newChain(1));

	// Reference problem input format
	scanf("%d %d", &a[1], &a[2]);
	scanf("%d %d %d", &x, &y, &z);
	for (int i = 3; i <= 2 * qn; i++) {
		a[i] = (1ll * x * a[i - 2] + 1ll * y * a[i - 1] + 1ll * z) % n;
	}

	int q1 = a[1], q2 = a[2]; 
	for (int i = 1; i <= qn; i++) {
		int cur = lca(q1 + 1, q2 + 1) - 1;
		ans += cur;
		q1 = (a[2 * (i + 1) - 1] + cur) % n;
		q2 = a[2 * (i + 1)];
	}

	cout << ans << endl;

	return 0;
}