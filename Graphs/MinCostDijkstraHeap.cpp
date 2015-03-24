/************************************************************************************

	Min Cost Flow (or Min Cost Max Flow) algorithm with
	Dijkstra algorithm (with potentials) as shortest path search method.
	(Dijkstra on heap for sparse graphs)
 
	Works (N * M ^ 2 * logN). Less on practice. 
	Runs in O(N ^ 3) for bipartite matching case.

	Based on problem 394 from informatics.mccme.ru 
	http://informatics.mccme.ru//mod/statements/view3.php?chapterid=394

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

const int MAXN = 1050;
const long long INF = (long long) 1e15;

struct edge {
	int from, to;
	int flow, cap;
	long long cost;
};

int n;
int cost[MAXN][MAXN];
vector <edge> e;
vector <int> g[MAXN];
long long phi[MAXN];
priority_queue < pair < long long, int > > q;
long long dist[MAXN];
int par[MAXN];
int edge_num;
int s = 0, t = MAXN - 1;

void fordBellman() {
	for (int i = s; i <= t; i++) 
		dist[i] = INF;
	dist[s] = 0;
	while (true) {
		bool change = false;
		for (int i = 0; i < edge_num; i++) {
			int from = e[i].from, to = e[i].to;
			if (e[i].flow == e[i].cap)
				continue;
			if (dist[from] == INF)
				continue;
			if (dist[to] > dist[from] + e[i].cost) {
				dist[to] = dist[from] + e[i].cost;
				change = true;
			}
		}
		if (!change)
			break;
	}
}

void dijkstra() {
	while (!q.empty())
		q.pop();
	for (int i = s; i <= t; i++) {
		dist[i] = INF;
		q.push(make_pair(-dist[i], i));
	}
	dist[s] = 0;
	q.push(make_pair(0, s));
	while (!q.empty()) {
		int cur = q.top().second;
		long long cur_dist = -q.top().first;
		q.pop();
		if (cur_dist > dist[cur])
			continue;
		if (dist[cur] == INF)
			break;
		for (int i = 0; i < (int) g[cur].size(); i++) {
			int ind = g[cur][i];
			if (e[ind].flow == e[ind].cap)
				continue;
			int to = e[ind].to;
			long long w = e[ind].cost + phi[cur] - phi[to];
			if (cur_dist + w < dist[to]) {
				dist[to] = cur_dist + w;
				par[to] = ind;
				q.push(make_pair(-dist[to], to));
			}
		}
	}
}

long long minCost(int flow) {
	long long result = 0;

	fordBellman();	
	for (int i = s; i <= t; i++)
		phi[i] = dist[i];

	while (true) {

		dijkstra();

		if (dist[t] == INF)
			return result;

		for (int i = s; i <= t; i++)
			phi[i] = min(phi[i] + dist[i], INF);

		int push = flow;
		int cur = t;
		while (cur != s) {
			edge tmp = e[par[cur]];
			int from = tmp.from, can_push = tmp.cap - tmp.flow;
			push = min(push, can_push);
			cur = from;
		}

		flow -= push;
		cur = t;
		while (cur != s) {
			edge tmp = e[par[cur]];
			int from = tmp.from;
			e[par[cur]].flow += push;
			e[par[cur] ^ 1].flow -= push;
			result += 1ll * push * tmp.cost;
			cur = from;
		}

		if (flow == 0)
			break;
	}
	return result;
}	

void addEdge(int from, int to, int cap, long long cost) {
	edge tmp;
	tmp.from = from; tmp.to = to; tmp.flow = 0; tmp.cap = cap; tmp.cost = cost;
	e.push_back(tmp);
	g[from].push_back(edge_num);

	tmp.from = to; tmp.to = from; tmp.flow = cap; tmp.cap = cap; tmp.cost = -cost;
	e.push_back(tmp);
	g[to].push_back(edge_num + 1);

	edge_num += 2;
}

int main() {
	//assert(freopen("input.txt","r",stdin));
	//assert(freopen("output.txt","w",stdout));

	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &cost[i][j]);

	s = 0; t = 2 * n + 1;

	for (int i = 1; i <= n; i++) 
		addEdge(s, i, 1, 0);

	for (int i = n + 1; i <= 2 * n; i++) 
		addEdge(i, t, 1, 0);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			addEdge(i, n + j, 1, cost[i][j]);

	cout << minCost(n) << endl;

	return 0;
}                             