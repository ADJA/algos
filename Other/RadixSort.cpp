/************************************************************************************

	Radix sort. O(N * len), where len - maximum length of numbers.
	Based on problem 766 from informatics.mccme.ru: 
	http://informatics.mccme.ru/mod/statements/view3.php?id=1129&chapterid=766

************************************************************************************/

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
#include <utility>
#include <iomanip>

using namespace std;

const int MAXN = 105000;

int n;
int a[MAXN];
vector <int> buckets[10];
int power = 1;
int minNum, maxNum;

int main() {
	//assert(freopen("input.txt","r",stdin));
	//assert(freopen("output.txt","w",stdout));

	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	minNum = a[1];
	for (int i = 2; i <= n; i++) {
		minNum = min(minNum, a[i]);
		maxNum = max(maxNum, a[i]);
	}

	for (int i = 1; i <= n; i++)
		a[i] -= minNum;

	while (true) {
	 	for (int i = 0; i < 10; i++)
	 		buckets[i].clear();

	 	for (int i = 1; i <= n; i++) {
	 		int digit = (a[i] / power) % 10;
	 		buckets[digit].push_back(a[i]);
	 	}

	 	n = 0;

	 	for (int i = 0; i < 10; i++)
	 		for (int j = 0; j < (int) buckets[i].size(); j++) {
	 			n++;
	 			a[n] = buckets[i][j];
	 		}

		power *= 10;
		if (power > maxNum)
			break;
	}

	for (int i = 1; i <= n; i++)
		printf("%d ", a[i] + minNum);

	return 0;
}