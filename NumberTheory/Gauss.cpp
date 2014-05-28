/*******************************************************************************

	Gauss method of solving system of linear algebraic equation.
	Works in O(n ^ 3) (more precisely - O(min(n, m) * n * m))

	Based on problem 198 from acmp.ru:
	http://acmp.ru/index.asp?main=task&id_task=198

*******************************************************************************/

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

const int MAXN = 150;
const int INF = 1 << 20;
const double eps = 1e-6;

int n, m;
double a[MAXN][MAXN];
double ans[MAXN];

// returns the number of solutions: 0, 1 or infinity 
// in case of any solution, it is written in the ans[] array
int gauss(int n, int m, double a[MAXN][MAXN], double ans[MAXN]) {
	int pos[MAXN];
	memset(pos, 0, sizeof(pos));

	bool parameters = false;
	int row = 1, col = 1;

	for (; row <= n && col <= m; col++) {
		int pivot = row; 
		for (int i = row; i <= n; i++) 
			if (abs(a[i][col]) > abs(a[pivot][col]))
				pivot = i;

		if (abs(a[pivot][col]) < eps) {
			parameters = true;
			continue;
		}

		for (int i = 1; i <= m + 1; i++)
			swap(a[row][i], a[pivot][i]);

		pos[col] = row;

		double div = a[row][col];
		for (int i = 1; i <= m + 1; i++)
			a[row][i] /= div;

		for (int i = 1; i <= n; i++) {
			if (i == row) 
				continue;
			div = a[i][col];
			for (int j = 1; j <= m + 1; j++)
				a[i][j] -= a[row][j] * div;
		}

		row++;
	}

	for (int i = 1; i <= m; i++)
		if (pos[i] != 0)
			ans[i] = a[pos[i]][m + 1];
		else
			ans[i] = 0;

	for (int i = 1; i <= n; i++) {
		double sum = 0;
		for (int j = 1; j <= m; j++)
			sum += ans[j] * a[i][j];
		if (abs(sum - a[i][m + 1]) > eps)
			return 0;
	}

	if (parameters)
		return INF;

	return 1;
}

int main() {
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);

	scanf("%d", &n);
	m = n;

	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= m + 1; j++)
			scanf("%lf", &a[i][j]);

	if (gauss(n, m, a, ans) == 1) {
		for (int i = 1; i <= m; i++) {
			ans[i] = floor(ans[i] + 0.5);
			printf("%.0lf ", ans[i]);
		}
	}

	return 0;
}