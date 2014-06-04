/***********

Solution to Closest Pair of Points Problem. O(nlogn) Divide-and-Conquer.
Tested on http://www.spoj.com/problems/CLOPPAIR/

***********/
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

#define sqr(a) ((a)*(a))
const double inf = 1e100;
const int MAXN = 55000;


struct point {
	double x, y;
	int ind;
	void read() {
		scanf("%lf%lf", &x, &y);
	}
	double dist_to(point& r) {
		return sqrt(sqr(x - r.x) + sqr(y - r.y));
	}
	bool operator<(const point&r) const {
		return x < r.x || (x == r.x && y < r.y);
	}
};

point aux[MAXN], P[MAXN], v[MAXN]; int vn;

int a, b, n;
double ans = inf;

// ans contains closest distance, a, b - indices of points.
void closest_pair(point p[], int n) {
	if (n <= 1) return ;
	if (n == 2) {
		if (p[0].y > p[1].y)
			swap(p[0], p[1]);
		double d = p[0].dist_to(p[1]);
		if (d < ans)
			ans = d, a = p[0].ind, b = p[1].ind;
		return;
	}
	int m = n / 2;
	double x = p[m].x;
	closest_pair(p, m); // left
	closest_pair(p + m, n - m); //right

	int il = 0, ir = m, i = 0;
	while (il < m && ir < n) { // merging two halves
		if (p[il].y < p[ir].y) aux[i ++] = p[il ++];
		else aux[i ++] = p[ir ++];
	}
	while (il < m)
		aux[i ++] = p[il ++];
	while (ir < n)
		aux[i ++] = p[ir ++];

	vn = 0;
	for (int j = 0 ; j < n ; j ++) { // copying back into p
		p[j] = aux[j];
		if (fabs(p[j].x - x) < ans) // looking at the strip of width 2*ans
			v[vn ++] = p[j];
	}

	for (int j = 0 ; j < vn ; j ++) { // (2*ans) x (ans) box
		for (int k = j + 1 ; k < vn && v[k].y - v[j].y < ans ; k ++) {
			double d = v[j].dist_to(v[k]);
			if (ans > d) {
				ans = d;
				a = v[k].ind, b = v[j].ind;
			}
		}
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 0 ; i < n ; i++) {
		P[i].read();
		P[i].ind = i;
	}
	sort(P, P + n);
	closest_pair(P, n);
	printf("%d %d %lf\n", min(a, b), max(a, b), ans);
	return 0;
}

