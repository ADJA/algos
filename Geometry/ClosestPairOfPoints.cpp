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

point aux[MAXN], P[MAXN];

int a, b, n;
double ans = inf;

// ans contains closest distance, a, b - indices of points.
double closest_pair(point p[], int n) {
	if (n <= 1) return inf;
	if (n == 2) {
		if (p[0].y > p[1].y)
			swap(p[0], p[1]);
		double d = p[0].dist_to(p[1]);
		if (d < ans)
			ans = d, a = p[0].ind, b = p[1].ind;
		return d;
	}
	int m = n / 2;
	double dl = closest_pair(p, m); // left
	double dr = closest_pair(p + m, n - m); //right
	double x = p[m].x;
	double d = min(dl, dr); 
	int il = 0, ir = m, i = 0;
	while (il < m && ir < n) { // merging two halves
		if (p[il].y < p[ir].y)
			aux[i ++] = p[il ++];
		else
			aux[i ++] = p[ir ++];
	}
	while (il < m)
		aux[i ++] = p[il ++];
	while (ir < n)
		aux[i ++] = p[ir ++];
	for (int j = 0 ; j < n ; j ++)
		p[j] = aux[j];
	for (int j = 0 ; j < n ; j ++) { // 2d x d box
		for (int k = j + 1 ; k < n && p[j].dist_to(p[k]) < d ; k ++) {
			if (d > p[j].dist_to(p[k])) {
				d = p[j].dist_to(p[k]);
				if (ans > d) {
					ans = d;
					a = p[k].ind, b = p[j].ind;
				}
			}			

		}
	}
	return d;
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

