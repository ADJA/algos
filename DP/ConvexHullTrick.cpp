/********************************************************************************

	Convex Hull trick. About it: http://wcipeg.com/wiki/Convex_hull_trick
	Based on CFR #189, task C: http://codeforces.ru/contest/319/problem/C

********************************************************************************/

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

int n;
long long height[MAXN], tax[MAXN];
long long dp[MAXN];
vector <long long> mvals, bvals;
int cur = 0;

// Suppose the last 3 lines added are : (l1, l2, l3)
// Line l2 becomes irrelevant, if l1/l3 x-intersection is to the left of l1/l2 x-intersection
bool bad(long long m1, long long b1, long long m2, long long b2, long long m3, long long b3) {
	// Cast to double to avoid long long overflow
	return 1.0 * (b1 - b3) * (m2 - m1) < 1.0 * (b1 - b2) * (m3 - m1);
}

void add(long long m, long long b) {
	while ( (int) mvals.size() >= 2 && bad(mvals[mvals.size() - 2], bvals[bvals.size() - 2], mvals[mvals.size() - 1], bvals[bvals.size() - 1], m, b)) {
		mvals.pop_back(); bvals.pop_back();
	}
	mvals.push_back(m); bvals.push_back(b);
}

void setCur(long long x) {
	if (cur > (int) mvals.size() - 1)
		cur = (int) mvals.size() - 1;
	// Best-line pointer goes to the right only when queries are non-decreasing (x argument grows)
	while (cur < (int) mvals.size() - 1 && 1.0 * mvals[cur + 1] * x + bvals[cur + 1] <= 1.0 * mvals[cur] * x + bvals[cur])
		cur++;
}

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%I64d", &height[i]);
	for (int i = 1; i <= n; i++)
		scanf("%I64d", &tax[i]);

	// Formula is dp[i] = min(tax[j] * height[i] + dp[j] | j = 1 .. i - 1)
	// Here tax[j] is considered as m value, and dp[j] as b value in line equation y = m * x + b 
	for (int i = 1; i <= n; i++) {
		if (i == 1) {
			dp[i] = 0;
		}
		else {
			setCur(height[i]);
			dp[i] = mvals[cur] * height[i] + bvals[cur]; 
		}
		add(tax[i], dp[i]);
	}

	cout << dp[n];

	return 0;
}