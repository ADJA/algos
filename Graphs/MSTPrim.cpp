/**************************************************************************************

	Minimum spanning tree using Prim algorithm. O(N ^ 2)

	Based on problem 185 from informatics.mccme.ru:
	http://informatics.mccme.ru/mod/statements/view3.php?id=261&chapterid=185

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

const long long INF = (long long) 1e12;
const int MAXN = 1050;

int n, m;
long long e[MAXN][MAXN];
long long dist[MAXN];
bool used[MAXN];
long long ans;

int main() {
	//assert(freopen("input.txt","r",stdin));
	//assert(freopen("output.txt","w",stdout));

	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			e[i][j] = INF;

	for (int i = 1; i <= m; i++) {
		int from, to, w;
		scanf("%d %d %d", &from, &to, &w);
		e[from][to] = e[to][from] = w;
	}

	dist[1] = 0;
	for (int i = 2; i <= n; i++)
		dist[i] = INF;

	for (int i = 1; i <= n; i++) {
		int cur = -1;
		for (int j = 1; j <= n; j++)
			if (!used[j] && (cur == -1 || dist[j] < dist[cur])) {
				cur = j;
			}

		used[cur] = true;
		ans += dist[cur];

		for (int j = 1; j <= n; j++) {
			if (used[j])
				continue;
			if (dist[j] > e[cur][j])
				dist[j] = e[cur][j];
		} 
	}                       	

	cout << ans << endl;

	return 0;
}