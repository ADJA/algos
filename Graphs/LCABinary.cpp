/************************************************************************************

	Finding LCA (Least common ancestor) of two vertices in the tree.
	Uses dp calculated on powers of 2. 
	O(NlogN) for preprocessing,	O(logN) on query.

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

const int MAXN = 405000;
const int MAXLOG = 22;

int n, qn;
vector <int> g[MAXN];   
int dp[MAXN][MAXLOG];
int tin[MAXN], tout[MAXN];
int timer;

int a[MAXN];
int x, y, z;
long long ans;

void dfs(int v, int par = 1) {
	timer++;
	tin[v] = timer;

	dp[v][0] = par;
	for (int i = 1; i < MAXLOG; i++) 
		dp[v][i] = dp[dp[v][i - 1]][i - 1];

	for (int i = 0; i < (int) g[v].size(); i++) {
		int to = g[v][i];
		if (to != par)
			dfs(to, v);
	}

	timer++;
	tout[v] = timer;
}

bool isParent(int a, int b) {
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
	if (isParent(a, b))
		return a;
	if (isParent(b, a))
		return b;
	for (int i = MAXLOG - 1; i >= 0; i--) { 
		if (!isParent(dp[a][i], b))
			a = dp[a][i];
	}
	return dp[a][0];
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