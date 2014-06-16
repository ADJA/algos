/**************************************************************************************

	Algorithm for finding all bridges in the graph (edges, after removal of
	which graph divides into several components). O(M)

	Based on problem C from here: http://codeforces.ru/gym/100083

**************************************************************************************/

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

int n, m;
vector <int> g[MAXN];
vector <int> ind[MAXN];
int tin[MAXN], mn[MAXN];
bool used[MAXN];
vector <int> bridges;
int timer;

void dfs(int v, int par = -1) {
	used[v] = true;
	timer++;
	tin[v] = timer;
	mn[v] = tin[v];

	for (int i = 0; i < (int) g[v].size(); i++) {
		int to = g[v][i];
		if (!used[to]) {
			dfs(to, v);
			if (mn[to] == tin[to]) {
				bridges.push_back(ind[v][i]);
			}
			mn[v] = min(mn[v], mn[to]);
		}
		else if (to != par) {
			mn[v] = min(mn[v], mn[to]);			
		}
	}
}

int main() {
	assert(freopen("bridges.in","r",stdin));
	assert(freopen("bridges.out","w",stdout));

	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++) {
		int from, to;
		scanf("%d %d", &from, &to);

		g[from].push_back(to);
		ind[from].push_back(i);

		g[to].push_back(from);
		ind[to].push_back(i);
	}

	for (int i = 1; i <= n; i++)
		if (!used[i])
			dfs(i);

	sort(bridges.begin(), bridges.end());

	printf("%d\n", (int) bridges.size());
	for (int i = 0; i < (int) bridges.size(); i++)
		printf("%d\n", bridges[i]);	

	return 0;
}