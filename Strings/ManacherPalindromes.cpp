/****************************************************************************

	Manacher's algorithm for finding all subpalindromes in the string.

	Based on problem L from here: http://codeforces.ru/gym/100133

****************************************************************************/

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

string s;
int n;
int odd[MAXN], even[MAXN];          
int l, r;
long long ans;

int main() {
	assert(freopen("palindrome.in","r",stdin));
	assert(freopen("palindrome.out","w",stdout));

	getline(cin, s);
	n = (int) s.length();

	// Odd case
	l = r = -1;
	for (int i = 0; i < n; i++) {
		int cur = 1;
		if (i < r)
			cur = min(r - i + 1, odd[l + r - i]);
		while (i + cur < n && i - cur >= 0 && s[i - cur] == s[i + cur])
			cur++;
		odd[i] = cur;
		if (i + cur - 1 > r) {
			l = i - cur + 1; 
			r = i + cur - 1;
		}
	}

	// Even case 
	l = r = -1;
	for (int i = 0; i < n; i++) {
		int cur = 0;
		if (i < r) 
			cur = min(r - i + 1, even[l + r - i + 1]);
		while (i + cur < n && i - 1 - cur >= 0 && s[i - 1 - cur] == s[i + cur])
			cur++;
		even[i] = cur;
		if (i + cur - 1 > r) {
			l = i - cur;
			r = i + cur - 1;
		}
	}

	for (int i = 0; i < n; i++) {
		if (odd[i] > 1) {
			ans += odd[i] - 1;
		}
		if (even[i])    
			ans += even[i];
	}

	cout << ans << endl;

	return 0;
}