/**************************************************************************************

	Algorithm for finding all cutpoints in the graph (vertices, after removal of
	which graph divides into several components). O(M)

	Based on problem D from here: http://codeforces.ru/gym/100083

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
int tin[MAXN], mn[MAXN];
bool used[MAXN];
vector <int> cutVertices;
int timer;

void dfs(int v, int par = -1) {
	used[v] = true;
	timer++;
	tin[v] = timer;
	mn[v] = tin[v];

	int childNum = 0;
	bool isCutVertex = false;

	for (int i = 0; i < (int) g[v].size(); i++) {
		int to = g[v][i];
		if (!used[to]) {
			childNum++;
			dfs(to, v);
			if (par != -1 && mn[to] >= tin[v] && !isCutVertex) {	
				isCutVertex = true;
				cutVertices.push_back(v);
			}
			mn[v] = min(mn[v], mn[to]);
		}
		else if (to != par) {
			mn[v] = min(mn[v], tin[to]);
		}
	}

	if (par == -1 && childNum > 1)
		cutVertices.push_back(v);
}

int main() {
	assert(freopen("points.in","r",stdin));
	assert(freopen("points.out","w",stdout));

	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++) {
		int from, to;
		scanf("%d %d", &from, &to);
		g[from].push_back(to);
		g[to].push_back(from);
	}

	for (int i = 1; i <= n; i++)
		if (!used[i])
			dfs(i);

	sort(cutVertices.begin(), cutVertices.end());

	printf("%d\n", (int) cutVertices.size());
	for (int i = 0; i < (int) cutVertices.size(); i++)
		printf("%d\n", cutVertices[i]);

	return 0;
}   