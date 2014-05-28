/**************************************************************************************

	Kuhn algorithm for maximum matching in bipartite graph. Works in O(N * M)
	More about it: http://e-maxx.ru/algo/kuhn_matching                      	
	Based on problem 1683 from informatics.mccme.ru:
	http://informatics.mccme.ru/moodle/mod/statements/view.php?chapterid=1683

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

const int MAXN = 105;

int n, m;
vector <int> g[MAXN];
bool used[MAXN];
int mt[MAXN];
int ans;

bool kuhn(int v) {
	if (used[v])
		return false;
	used[v] = true;
	for (int i = 0; i < (int) g[v].size(); i++) {
		int to = g[v][i];
		if (mt[to] == 0 || kuhn(mt[to])) {
			mt[to] = v;
			return true;
		}
	}	
	return false;
}

int main() {
	//assert(freopen("input.txt","r",stdin));
	//assert(freopen("output.txt","w",stdout));

	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int can;
			scanf("%d", &can);
			if (can)
				g[i].push_back(j);
		}
	}

	for (int i = 1; i <= n; i++) {
		memset(used, 0, sizeof(used));
		if (kuhn(i))
			ans++;
	}

	printf("%d\n", ans);

	return 0;
}