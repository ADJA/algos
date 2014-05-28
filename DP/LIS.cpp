/****************************************************************************************************

	Finding Longest Increasing Sequence in O(NlogN)
	About it: http://e-maxx.ru/algo/longest_increasing_subseq_log
	Based on problem http://informatics.mccme.ru/mod/statements/view3.php?id=766&chapterid=1794

****************************************************************************************************/

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
const int INF = 1000 * 1000 * 1000;

int n;
int k, b, m; 
int a[MAXN];
int d[MAXN];
int ind[MAXN], pr[MAXN];
vector <int> ansv;
int ans = 1;

int main() {
	//assert(freopen("input.txt","r",stdin));
	//assert(freopen("output.txt","w",stdout));

	scanf("%d", &n);
	scanf("%d %d %d %d", &a[1], &k, &b, &m);

	for (int i = 2; i <= n; i++)
		a[i] = (k * a[i - 1] + b) % m; 

	d[0] = -INF;
	for (int i = 1; i <= n; i++)
		d[i] = INF;

	for (int i = 1; i <= n; i++) {
		int pos = upper_bound(d + 1, d + n + 1, a[i]) - d;
		if (d[pos - 1] < a[i] && a[i] < d[pos]) {
			d[pos] = a[i];
			ind[pos] = i;
			pr[i] = ind[pos - 1];
			if (pos > ans) {
				ans = pos;
			}
		}
	}

	if (ans == 1) {
		printf("%d", a[1]);
	}
	else {
		int cur = ind[ans];
		while (cur != 0) {
			ansv.push_back(a[cur]);
			cur = pr[cur];
		}

		for (int i = (int) ansv.size() - 1; i >= 0; i--)
			printf("%d ", ansv[i]);	
	}

	return 0;                                      
}