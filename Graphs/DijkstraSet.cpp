/**************************************************************************************
    
     Dijkstra on set for sparse graphs - O(MlogM). Slower than heap version
     Based on problem 20C from codeforces: http://codeforces.ru/contest/20/problem/C

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

const long long INF = (long long)1e12;
const int MAXN = 105000;

struct edge {
	int to, w;
};

int n, m;
vector <edge> g[MAXN];
long long dist[MAXN];
int par[MAXN];
set < pair<long long, int> > s;
vector <int> ans;
edge e;

int main() {
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int a, b, w;
		scanf("%d %d %d", &a, &b, &w);
		e.to = b; e.w = w;
		g[a].push_back(e);
		e.to = a;
		g[b].push_back(e);
	}

	s.insert(make_pair(0, 1));
	for (int i = 2; i <= n; i++) {
		dist[i] = INF;
		s.insert(make_pair(INF, i));
	}

	while (!s.empty()) {
		int cur = s.begin()->second;
		long long cur_dist = s.begin()->first;
		s.erase(s.begin());
		for (int i = 0; i < (int) g[cur].size(); i++) {
			int to = g[cur][i].to, w = g[cur][i].w;
			if (cur_dist + w < dist[to]) {
				s.erase(make_pair(dist[to], to));
				dist[to] = cur_dist + w;
				par[to] = cur;
				s.insert(make_pair(dist[to], to));
			}
		}
	}

	if (dist[n] == INF) {
		printf("-1");
		return 0;
	}

	int cur = n;
	while (par[cur] != 0) {
		ans.push_back(cur);
		cur = par[cur];
	}
	ans.push_back(1);

	reverse(ans.begin(), ans.end());
	for (int i = 0; i < (int) ans.size(); i++)
		printf("%d ", ans[i]);

	return 0;
}