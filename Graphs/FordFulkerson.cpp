/********************************************************************************

	MaxFlow Ford-Fulkerson algorithm. O(M|f|), |f| - maxflow value
	Based on problem 2783 from informatics.mccme.ru 
	http://informatics.mccme.ru/mod/statements/view3.php?chapterid=2783#1

********************************************************************************/

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

const int MAXN = 1050;
const int INF = (int) 1e9;

struct edge {
	int from, to, f, cap;
};

int n, m;
vector <edge> e;
vector <int> g[MAXN];
bool used[MAXN];
int s, t;
int ans;

void addEdge(int from, int to, int cap) {
	edge ed;

	ed.from = from; ed.to = to; ed.f = 0; ed.cap = cap;
	e.push_back(ed);
	g[from].push_back((int) e.size() - 1);

	ed.from = to; ed.to = from; ed.f = cap; ed.cap = cap;
	e.push_back(ed);
	g[to].push_back((int) e.size() - 1);
}

int pushFlow(int v, int flow = INF) {
	used[v] = true;
	if (v == t)
		return flow;	

	for (int i = 0; i < (int) g[v].size(); i++) {
		int ind = g[v][i];
		int to = e[ind].to; 
		int f = e[ind].f;
		int cap = e[ind].cap;

		if (used[to] || cap - f == 0)
			continue;

		int pushed = pushFlow(to, min(flow, cap - f));
		if (pushed > 0) {
			e[ind].f += pushed;
			e[ind ^ 1].f -= pushed;
			return pushed;
		}
	}

	return 0;	
}

int main() {
	//assert(freopen("input.txt","r",stdin));
	//assert(freopen("output.txt","w",stdout));

	scanf("%d %d", &n, &m);

	s = 1; t = n;

	for (int i = 1; i <= m; i++) {
		int from, to, cap;
		scanf("%d %d %d", &from, &to, &cap);
		addEdge(from, to, cap);
	}

	while (true) {
		memset(used, 0, sizeof(used));
		int add = pushFlow(s);
		if (add == 0)
			break;
		ans += add;
	}

	printf("%d\n", ans);

	return 0;
}