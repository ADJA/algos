/**********************************************************************************

	Finding the closest pair of points. O(NlogN), divide-and-conquer.
	Based on http://www.spoj.com/problems/CLOPPAIR/

**********************************************************************************/

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

#define sqr(x) ((x) * (x))

const double inf = 1e100;   
const int MAXN = 105000;

struct point {
	double x, y;
	int ind;
};

bool cmp(point a, point b) {
	return (a.x < b.x || (a.x == b.x && a.y < b.y));
}

double dist(point a, point b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

int n;
int a[MAXN];
point p[MAXN], tmp[MAXN];
double ans = inf;
int p1, p2;

void updateAnswer(point a, point b) {
	double d = dist(a, b);
	if (d < ans) {
		ans = d;
		p1 = a.ind; p2 = b.ind;
	}
}

void closestPair(int l, int r) {
	if (l >= r)
		return;

	if (r - l == 1) {
		if (p[l].y > p[r].y)
			swap(p[l], p[r]);
		updateAnswer(p[l], p[r]);
		return;
	}

	int m = (l + r) / 2;
	double mx = p[m].x;

	closestPair(l, m);
	closestPair(m + 1, r);

	int lp = l, rp = m + 1, sz = 1;
	while (lp <= m || rp <= r) {
		if (lp > m || ((rp <= r && p[rp].y < p[lp].y))) {
			tmp[sz] = p[rp];
			rp++;
		}
		else {
			tmp[sz] = p[lp];
			lp++;
		}
		sz++;
	}

	for (int i = l; i <= r; i++) 
		p[i] = tmp[i - l + 1];

	sz = 0;
	for (int i = l; i <= r; i++)
		if (abs(p[i].x - mx) < ans) {
			sz++;
			tmp[sz] = p[i];
		}

	for (int i = 1; i <= sz; i++) {
		for (int j = i - 1; j >= 1; j--) {
			if (tmp[i].y - tmp[j].y >= ans)
				break;
			updateAnswer(tmp[i], tmp[j]);
		}
	}
}

int main() {
	//assert(freopen("input.txt","r",stdin));
	//assert(freopen("output.txt","w",stdout));

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lf %lf", &p[i].x, &p[i].y);
		p[i].ind = i - 1;
	}

	sort(p + 1, p + n + 1, cmp);

	closestPair(1, n);

	printf("%d %d %.6lf\n", min(p1, p2), max(p1, p2), ans);

	return 0;
}