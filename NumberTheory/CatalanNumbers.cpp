/*******************************************************************************

	Finding Nth Catalan number modulo some mod 
	(N <= 500000, mod is not necessary prime)
	
	Uses Eratosthenes sieve for fast factorization
	Works in O(N * loglogN)

	Based on problem 140 from acm.mipt.ru
	http://acm.mipt.ru/judge/problems.pl?problem=140

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

const int MAXN = 500500;

int n, mod;
int sieve[2 * MAXN];
int p[2 * MAXN];
long long ans = 1;

int main() {
	//assert(freopen("input.txt","r",stdin));
	//assert(freopen("output.txt","w",stdout));
	
	scanf("%d %d", &n, &mod);

	for (int i = 2; i <= 2 * n; i++) {
		if (sieve[i] == 0) {
			for (int j = 2 * i; j <= 2 * n; j += i) {
				if (sieve[j] == 0)
					sieve[j] = i;
			}
		}
	}

	for (int i = n + 2; i <= 2 * n; i++) {
		int x = i;
		while (sieve[x] != 0) {
			p[sieve[x]]++;
			x /= sieve[x];
		}
		p[x]++;
	}

	for (int i = 1; i <= n; i++) {
		int x = i;
		while (sieve[x] != 0) {
			p[sieve[x]]--;
			x /= sieve[x];
		}
		p[x]--;
	}

	for (int i = 2; i <= 2 * n; i++) {
		for (int j = 1; j <= p[i]; j++)	
			ans = (1ll * ans * i) % mod;
	}

	cout << ans % mod << endl;

	return 0;
}