/************************************************************************

	Suffix Tree. Ukkonen's algorithm using sibling lists — O(N).

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

#define root 1

const int MAXN = 105000;
const int inf = 1000 * 1000 * 1000;

struct node {
	int from, to, link;
	int child, bro;
};

int n, len, nk, pos;
string s;
vector <node> tree;
int active_e, active_node, active_len, needSL, rem;

int add_node(int from, int to) {
	nk++;
	node temp; 
	temp.from = from; temp.to = to; temp.link = 0;
	temp.child = 0; temp.bro = 0;
	tree.push_back(temp);
	return nk;
}

void st_init() {
	nk = -1;
	pos = -1;
	rem = active_e = active_len = needSL = 0;
	active_node = root;
	add_node(-1, -1);
	add_node(-1, -1);
}

void addSL(int v) {
	if (needSL) tree[needSL].link = v;
	needSL = v;
}

int find_edge(int v, int c) {
	v = tree[v].child;
	while (v) {
		if (s[tree[v].from] == c)
			return v;
		v = tree[v].bro;
	}
	return 0;
}

void insert_edge(int v, int to) {
	int temp = tree[v].child; 
	tree[v].child = to; 
	tree[to].bro = temp;
}

void change_edge(int v, int c, int to) {
	int next = tree[v].child;
	if (s[tree[next].from] == c) {
		tree[v].child = to;
		tree[to].bro = tree[next].bro;
		return;
	}
	v = next;
	while (v) {
		next = tree[v].bro;
		if (s[tree[next].from] == c) {
			tree[v].bro = to;
			tree[to].bro = tree[next].bro;
			return;
		}
		v = next;
	}
}

bool walk_down(int v) {
	int elen = tree[v].to - tree[v].from;
	if (tree[v].from + active_len >= tree[v].to) {
		active_node = v;
		active_len -= elen;
		active_e += elen;
		return true;
	}
	return false;
}

int active_edge() {
	return s[active_e];
}

void st_insert(int c) {
	pos++;
	needSL = 0; rem++; 
	while (rem) {
		if (active_len == 0) active_e = pos;
		int go = find_edge(active_node, active_edge());
		if (go == 0) {
			int leaf = add_node(pos, inf);
			insert_edge(active_node, leaf);
			addSL(active_node);
		}
		else {
			if (walk_down(go)) 
				continue;
			if (s[tree[go].from + active_len] == c) {
				active_len++;
				addSL(active_node);
				break;
			}
			int split = add_node(tree[go].from, tree[go].from + active_len);
			int leaf = add_node(pos, inf);

			change_edge(active_node, active_edge(), split);
			insert_edge(split, go);
			insert_edge(split, leaf);

			tree[go].from = tree[go].from + active_len;

			addSL(split);
		}
		rem--;
		if (active_node == root && active_len) {
			active_len--;
			active_e = pos - rem + 1;
		}
		else {
			if (tree[active_node].link) 
				active_node = tree[active_node].link;
			else
				active_node = root;
		}
	}
}

int count_diff() {
	int result = 0;
	for (int i = 2; i <= nk; i++)
		result += min(tree[i].to, n) - tree[i].from;
	return result;
}

int main() {
	freopen("substr.in","r",stdin);
	freopen("substr.out","w",stdout);

	getline(cin, s);
	n = (int) s.length();

	st_init();
	for (int i = 0; i < n; i++)
		st_insert(s[i]);

	printf("%d", count_diff());

	return 0;
}