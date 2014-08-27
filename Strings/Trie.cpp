/****************************************************************************

	Trie. Builds tree from the set of strings. O(total length of strings)

	This code counts number of different substrings in the string.           
	Based on problem B from here: http://codeforces.ru/gym/100133

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

const int ALPH = 26;
const int MAXN = 100500;

struct node {
	int go[ALPH];
};

string s;
node trie[MAXN];
int node_num;

int main() {
	assert(freopen("unequal.in","r",stdin));
	assert(freopen("unequal.out","w",stdout));

	getline(cin, s);

	for (int i = 0; i < (int) s.length(); i++) {
		int cur = 0;
		for (int j = i; j < (int) s.length(); j++) {
			int ch = s[j] - 'a';
			if (trie[cur].go[ch] == 0) {
				node_num++;
				trie[cur].go[ch] = node_num;
			}       
			cur = trie[cur].go[ch];
		}
	}

	printf("%d\n", node_num);

	return 0;
}