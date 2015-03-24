/************************************************************************

	Suffix Array. Builing works in O(NlogN).
	Also LCP array is calculated in O(NlogN).

	This code counts number of different substrings in the string.
	Based on problem I from here: http://codeforces.ru/gym/100133

************************************************************************/

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

const int MAXN = 205000;
const int ALPH = 256;
const int MAXLOG = 20;

int n;
char s[MAXN];
int p[MAXN]; // suffix array itself
int pcur[MAXN];
int c[MAXN][MAXLOG];
int num[MAXN];
int classesNum;
int lcp[MAXN];

void buildSuffixArray() {
	n++;

	for (int i = 0; i < n; i++) 
		num[s[i]]++;	

	for (int i = 1; i < ALPH; i++)
		num[i] += num[i - 1];

	for (int i = 0; i < n; i++) {
		p[num[s[i]] - 1] = i;
		num[s[i]]--;
	}

	c[p[0]][0] = 1;
	classesNum = 1;
	for (int i = 1; i < n; i++) {
		if (s[p[i]] != s[p[i - 1]])
			classesNum++;
		c[p[i]][0] = classesNum;
	}

	for (int i = 1; ; i++) {
		
		int half = (1 << (i - 1));		
		
		for (int j = 0; j < n; j++) {
			pcur[j] = p[j] - half;
			if (pcur[j] < 0)
				pcur[j] += n;	
		}

		for (int j = 1; j <= classesNum; j++)
			num[j] = 0;

		for (int j = 0; j < n; j++) 
			num[c[pcur[j]][i - 1]]++;
		for (int j = 2; j <= classesNum; j++)
			num[j] += num[j - 1];
        
		for (int j = n - 1; j >= 0; j--) {
			p[num[c[pcur[j]][i - 1]] - 1] = pcur[j];
			num[c[pcur[j]][i - 1]]--;
		}

		c[p[0]][i] = 1;
		classesNum = 1;

		for (int j = 1; j < n; j++) {
			int p1 = (p[j] + half) % n, p2 = (p[j - 1] + half) % n;
			if (c[p[j]][i - 1] != c[p[j - 1]][i - 1] || c[p1][i - 1] != c[p2][i - 1])
				classesNum++;
			c[p[j]][i] = classesNum;
		}

		if ((1 << i) >= n)
			break;
	}

	for (int i = 0; i < n; i++)
		p[i] = p[i + 1];
	n--;
}

int getLcp(int a, int b) {
	int res = 0;
	for (int i = MAXLOG - 1; i >= 0; i--) {
		int curlen = (1 << i);
		if (curlen > n)
			continue;
		if (c[a][i] == c[b][i]) {
			res += curlen;
			a += curlen;
			b += curlen;
		}
	}
	return res;
}

void calcLcpArray() {
	for (int i = 0; i < n - 1; i++)
		lcp[i] = getLcp(p[i], p[i + 1]);
}

int main() {
	assert(freopen("substr.in","r",stdin));
	assert(freopen("substr.out","w",stdout));

	gets(s);
	n = strlen(s);

	buildSuffixArray();

	// Now p from 0 to n - 1 contains suffix array of original string

	/*for (int i = 0; i < n; i++) {
		printf("%d ", p[i] + 1);
	}*/

    calcLcpArray();

	long long ans = 0;
	for (int i = 0; i < n; i++)
		ans += n - p[i];
	for (int i = 1; i < n; i++)
		ans -= lcp[i - 1];

	cout << ans << endl;

	return 0;
}                           