/*************************************************************************************

	Prefix function. O(N)

	About it: http://e-maxx.ru/algo/prefix_function
	Based on problem 1323 from informatics.mccme.ru:
	http://informatics.mccme.ru/mod/statements/view3.php?id=241&chapterid=1323

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

int n;
string s;
int p[MAXN];

int main() {
	//assert(freopen("input.txt","r",stdin));
	//assert(freopen("output.txt","w",stdout));

	getline(cin, s);
	n = (int) s.length();

	for (int i = 2; i <= n; i++) {
		int prev = p[i - 1];
		while (prev > 0 && s[prev] != s[i - 1])
			prev = p[prev];
		if (s[prev] == s[i - 1])
			prev++;
		p[i] = prev;
	}

	for (int i = 1; i <= n; i++)
		printf("%d ", p[i]);

	return 0;
}