/*******************************************************************************

	Finding number of permutation in lexicographical order
	Works in O(n^2)

	Based on problem 2388 from e-olimp.com
	http://www.e-olimp.com/problems/2388

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

const int MAXN = 20;

int n;
int f[MAXN];
int p[MAXN];
bool used[MAXN];
int ans;

int main() {
	//assert(freopen("input.txt","r",stdin));
	//assert(freopen("output.txt","w",stdout));

	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &p[i]);

	f[0] = 1;
	for (int i = 1; i <= n; i++)
		f[i] = f[i - 1] * i;

	ans = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (used[j])
				continue;
			if (p[i] == j) {
				used[j] = true;
				break;
			}
			ans += f[n - i];	
		}                  
	}

	printf("%d\n", ans);

	return 0;
}