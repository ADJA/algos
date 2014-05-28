/*************************************************************************************

	Z function. O(N)

	About it: http://e-maxx.ru/algo/z_function
	Based on problem 1324 from informatics.mccme.ru:
	http://informatics.mccme.ru/mod/statements/view3.php?id=241&chapterid=1324

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

const int MAXN = 1000100;

string s;
int n;
int z[MAXN];
int l, r;

int main() {
	//assert(freopen("input.txt","r",stdin));
	//assert(freopen("output.txt","w",stdout));

	getline(cin, s);
	n = (int) s.length();

	l = r = 0;
	for (int i = 2; i <= n; i++) {
		int cur = 0;
		if (i <= r)
			cur = min(r - i + 1, z[i - l + 1]);
		while (i + cur <= n && s[i + cur - 1] == s[cur])
			cur++;
		if (i + cur - 1 > r) {
			l = i; r = i + cur - 1;
		}
		z[i] = cur;
	}

	z[1] = n;
	for (int i = 1; i <= n; i++)
		printf("%d ", z[i]);

	return 0;
}