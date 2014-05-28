/************************************************************************************

	Quick sort with random pivot element. O(NlogN).
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
#include <cassert>
#include <utility>
#include <iomanip>

using namespace std;

const int MAXN = 105000;

int n;
int a[MAXN];

void qsort(int l, int r) {
	if (l >= r)
		return;

	int pivot = l + rand() % (r - l);
	int key = a[pivot];

	int i = l, j = r;
	while (i <= j) {
		while (a[i] < key)
			i++;
		while (a[j] > key)
			j--;
		if (i <= j) {
			swap(a[i], a[j]);
			i++; j--;
		}
	}

	if (l < j)
		qsort(l, j);
	if (i < r)
		qsort(i, r);	
}

int main() {
	//assert(freopen("input.txt","r",stdin));
	//assert(freopen("output.txt","w",stdout));

	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	qsort(1, n);

	for (int i = 1; i <= n; i++)
		printf("%d ", a[i]);

	return 0;
}