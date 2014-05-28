/********************************************************************************

	MaxFlow Dinic algorithm with scaling. ~ O(NMlogN)
	Based on problem 2784 from informatics.mccme.ru 
	http://informatics.mccme.ru/mod/statements/view3.php?chapterid=2784#1

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
#include <utility>
#include <iomanip>

using namespace std;

struct edge {
	int a, b, f, c;
	int ind;
};

const int inf = 1000 * 1000 * 1000;
const int MAXN = 1050;

int n, m;
vector <edge> e;
int pt[MAXN]; // very important performance trick
vector <int> g[MAXN];
long long flow = 0;
queue <int> q;
int d[MAXN];
int lim;

void add_edge(int a, int b, int c, int ind) {                                                                           
	edge ed;

	//keep edges in vector: e[ind] - direct edge, e[ind ^ 1] - back edge 

	ed.a = a; ed.b = b; ed.f = 0; ed.c = c; ed.ind = ind;
	g[a].push_back(e.size());
	e.push_back(ed);

	ed.a = b; ed.b = a; ed.f = c; ed.c = c; ed.ind = ind;
	g[b].push_back(e.size());
	e.push_back(ed);
}

bool bfs() {
	for (int i = 1; i <= n; i++)
		d[i] = inf;
	d[1] = 0; 
	q.push(1);
	while (!q.empty() && d[n] == inf) {
		int cur = q.front(); q.pop();
		for (size_t i = 0; i < g[cur].size(); i++) {
			int id = g[cur][i];
			int to = e[id].b;

			//printf("cur = %d id = %d a = %d b = %d f = %d c = %d\n", cur, id, e[id].a, e[id].b, e[id].f, e[id].c);


			if (d[to] == inf && e[id].c - e[id].f >= lim) {
				d[to] = d[cur] + 1;
				q.push(to);
			}
		}
	}
	while (!q.empty()) 
		q.pop();
	return d[n] != inf;
}

bool dfs(int v, int flow) {
	if (flow == 0) 
		return false;
	if (v == n) {
		//cout << v << endl;
		return true;
	}
	for (; pt[v] < g[v].size(); pt[v]++) {
		int id = g[v][pt[v]];
		int to = e[id].b;

		//printf("v = %d id = %d a = %d b = %d f = %d c = %d\n", v, id, e[id].a, e[id].b, e[id].f, e[id].c);

		if (d[to] == d[v] + 1 && e[id].c - e[id].f >= flow) {
			int pushed = dfs(to, flow); 
			if (pushed) {
				e[id].f += flow;
				e[id ^ 1].f -= flow;
				return true;
			}				
		}
	}
	return false;
}

void dinic() {
	for (lim = (1 << 30); lim >= 1;) {
		if (!bfs()) {
			lim >>= 1;
			continue;
		}

		for (int i = 1; i <= n; i++) 
			pt[i] = 0;

		int pushed;

		while (pushed = dfs(1, lim)) { 
			flow = flow + lim;
		}

		//cout << flow << endl;
	}
}

int main() {
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		add_edge(a, b, c, i);
	}

	dinic();

	cout << flow << endl;

	return 0;
}