/*************************************************************************************

	Sparse table. Solves static RMQ problem (without element changes).
	O(NlogN) on precalculation, O(1) on query.

	Based on problem 3309 from informatics.mccme.ru: 
	http://informatics.mccme.ru/moodle/mod/statements/view.php?chapterid=3309

*************************************************************************************/

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

const int MAXN = 2 * 105000;
const int MAXLOG = 20;

int n, m;
int a[MAXN];
int table[MAXLOG][MAXN];
int numlog[MAXN];

void buildTable() {
	numlog[1] = 0;
	for (int i = 2; i <= n; i++)
		numlog[i] = numlog[i / 2] + 1;

	for (int i = 0; i <= numlog[n]; i++) {
		int curlen = 1 << i;
		for (int j = 1; j <= n; j++) {
			if (i == 0) {
				table[i][j] = a[j];
				continue;
			}
			table[i][j] = max(table[i - 1][j], table[i - 1][j + curlen / 2]);
		}
	}
}

int getMax(int l, int r) {
	int curlog = numlog[r - l + 1];
	return max(table[curlog][l], table[curlog][r - (1 << curlog) + 1]); 
}

int main() {
	//assert(freopen("input.txt","r",stdin));
	//assert(freopen("output.txt","w",stdout));

	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	buildTable();

	scanf("%d", &m);

	for (int i = 1; i <= m; i++) {
		int l, r;
		scanf("%d %d", &l, &r);
		printf("%d ", getMax(l, r));
	}

	return 0;
}