/************************************************************************************

	Algorithm for finding Eulerian path/cycle (path that visits every edge
	exactly once). O(M).

	Based on problem 1704 from informatics.mccme.ru 
	http://informatics.mccme.ru/mod/statements/view3.php?chapterid=1704

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

struct edge {
	int to;
	int gate1, gate2;
	bool used;
};

int n;
vector <edge> e;
vector <int> g[MAXN];
int pos[MAXN];
edge tmp;
bool used[MAXN];
vector <int> ans;

/*
	Eulerian walk search. Criterias are neglected in this problem.
	Eulerian cycle criteria - all vertices have even degree.
	Eulerian path criteria - maximum 2 vertices have odd degree. Path is found 
	from cycle: add extra edge, find cycle, remove edge.
*/
void dfs(int v) {
	for (; pos[v] < (int) g[v].size(); pos[v]++) {
		int ind = g[v][pos[v]];
		int to = e[ind].to;
		if (e[ind].used)
			continue;
		e[ind].used = true; e[ind ^ 1].used = true;
		dfs(e[ind].to);
	}	
	ans.push_back(v);
	used[v] = true;
}

int main() {
	//assert(freopen("input.txt","r",stdin));
	//assert(freopen("output.txt","w",stdout));

	scanf("%d", &n);
	for (int i = 1; i <= 2 * n; i++) {
		int gate1, gate2;
		int from, to;
		scanf("%d %d", &gate1, &gate2);
		from = (gate1 + 3) / 4; to = (gate2 + 3) / 4;

		tmp.used = false;
		tmp.to = to; tmp.gate1 = gate1; tmp.gate2 = gate2;
		e.push_back(tmp);
		g[from].push_back( (int) e.size() - 1 );

		tmp.to = from; tmp.gate1 = gate2; tmp.gate2 = gate1;
		e.push_back(tmp);
		g[to].push_back( (int) e.size() - 1 );
	}

	dfs(1);

	for (int i = 1; i <= n; i++) {
		if (!used[i]) {
			puts("No");
			return 0;
		}
	}

	puts("Yes");

	/*
		Ans contains all vertices in the right order for Eulerian walk.
		Output specific to this problem.
	*/
	reverse(ans.begin(), ans.end());
	for (int i = 0; i < (int) ans.size() - 1; i++) {
		int from = ans[i], to = ans[i + 1];
		for (int j = 0; j < (int) g[from].size(); j++) {
			int ind = g[from][j];
			if (e[ind].to == to && e[ind].used) {
				printf("%d %d ", e[ind].gate1, e[ind].gate2);
				e[ind].used = false;
				e[ind ^ 1].used = false;
				break;
			}
		}
	}	

	return 0;
}