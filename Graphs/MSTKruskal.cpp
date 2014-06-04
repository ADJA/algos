/**************************************************************************************

	Minimum spanning tree using Kruskal algorithm with DSU. O(MlogM)

	Based on problem 1377 from informatics.mccme.ru:
	http://informatics.mccme.ru/mod/statements/view3.php?id=261&chapterid=1377

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

const int MAXN = 20500;

struct edge {
	int from, to, w;
};

bool cmp(edge a, edge b) {
	return a.w < b.w;
}

int n, m;
vector <edge> e;
int st[MAXN];
long long ans;

int getSet(int x) {
	if (st[x] == x)
		return x;
	st[x] = getSet(st[x]);
	return st[x];
}

void unite(int a, int b) {
	a = getSet(a); b = getSet(b);
	if (rand() & 1)
		swap(a, b);
	st[a] = b;
}

int main() {
	//assert(freopen("input.txt","r",stdin));
	//assert(freopen("output.txt","w",stdout));

	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) {
		edge add;
		scanf("%d %d %d", &add.from, &add.to, &add.w);
		e.push_back(add);
	}

	for (int i = 1; i <= n; i++)
		st[i] = i;

	sort(e.begin(), e.end(), cmp);

	for (int i = 0; i < (int) e.size(); i++) {
		int	from = getSet(e[i].from), to = getSet(e[i].to);
		if (from != to) {
			ans += e[i].w;
			unite(from, to);
		}
	}

	cout << ans << endl;

	return 0;
}