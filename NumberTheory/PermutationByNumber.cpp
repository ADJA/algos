/*******************************************************************************

	Finding permutation by its length and number in lexicographical order
	Works in O(n^2)

	Based on problem 190 from informatics.mccme.ru
	http://informatics.mccme.ru/moodle/mod/statements/view.php?chapterid=190#1

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

int n, num;
bool used[MAXN];
int f[MAXN];

void permutationByNumber(int n, int num) {
	for (int i = 1; i <= n; i++)
		used[i] = false;	

	int cur = 0;
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (used[j])
				continue;
			int add = f[n - i];
			if (cur + add >= num) {
				used[j] = true;
				printf("%d ", j);
				break;
			}
			cur += add;
		}
	}
	printf("\n");
}

int main() {
	//assert(freopen("input.txt","r",stdin));
	//assert(freopen("output.txt","w",stdout));

	scanf("%d", &n);
	scanf("%d", &num);

	f[0] = 1;
	for (int i = 1; i <= n; i++) {
		f[i] = f[i - 1] * i;
	}
	
	permutationByNumber(n, num);

	return 0;
}