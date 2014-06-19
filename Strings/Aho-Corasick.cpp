/******************************************************************************

	Aho-Corasick algorithm.

	This code finds all words in the text that contain any of the 
	initially given words. O(len of queries + sum len of initial strings)	


	Based on problem K from here: http://codeforces.ru/gym/100133

******************************************************************************/

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

struct node {
	int suff_link, par;
	char c;
	map < char, int > go;
	bool is_word;   

	node() {
		suff_link = -1, par = -1;
		is_word = false;
	}
};

int n;
char s[MAXN];
vector <node> trie;

void trieInsert(char s[MAXN]) {
	int cur_node = 0;
	int len = strlen(s);
	for (int i = 0; i < len; i++) {
		int go = trie[cur_node].go[s[i]];
		if (go == 0) {
			node add;
			add.par = cur_node; add.c = s[i];
			trie.push_back(add);
			go = (int) trie.size() - 1;
			trie[cur_node].go[s[i]] = go;
		}
		cur_node = go;
	}   
	trie[cur_node].is_word = true;
}

int go(int cur_node, char c);

int getSuffLink(int cur_node) {
	if (trie[cur_node].suff_link != -1)
		return trie[cur_node].suff_link;
	if (trie[cur_node].par == 0) 
		return trie[cur_node].suff_link = 0;
	char c = trie[cur_node].c;
	int parent = trie[cur_node].par;
	return trie[cur_node].suff_link = go(trie[parent].suff_link, c); 
}

int go(int cur_node, char c) {
	if (trie[cur_node].go.count(c) > 0)
		return trie[cur_node].go[c];
	if (cur_node == 0)
		return trie[cur_node].go[c] = 0;
	int suff_link = getSuffLink(cur_node);
	return trie[cur_node].go[c] = go(suff_link, c);
}

void buildAhoCorasick() {
	queue <int> q;
	q.push(0);
	while (!q.empty()) {
		int cur_node = q.front();
		q.pop();

		for (map <char, int> :: iterator it = trie[cur_node].go.begin(); it != trie[cur_node].go.end(); it++) {
			q.push(it->second);
		}

		int suff_link = getSuffLink(cur_node);
		trie[cur_node].suff_link = suff_link;
		if (trie[suff_link].is_word)
			trie[cur_node].is_word = true;
	}
}

int main() {
	assert(freopen("console.in","r",stdin));
	assert(freopen("console.out","w",stdout));

	node root;
	root.suff_link = 0;
	trie.push_back(root);

	scanf("%d", &n);
	gets(s);

	for (int i = 1; i <= n; i++) {
		gets(s);
		trieInsert(s);
	}

	buildAhoCorasick();

	while (gets(s)) {
		int cur_node = 0;
		int len = strlen(s);
		for (int i = 0; i < len; i++) {
			cur_node = go(cur_node, s[i]);
			if (trie[cur_node].is_word) {
				puts(s);
				break;
			}
		}
	}

	return 0;
}