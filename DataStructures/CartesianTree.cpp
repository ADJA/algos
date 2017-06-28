/*************************************************************************************

    Cartesian tree. Can be used as a balanced binary search tree.
    O(logN) on operation.

    Based on problem 2782 from informatics.mccme.ru: 
    http://informatics.mccme.ru/mod/statements/view3.php?chapterid=2782

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
#include <utility>
#include <iomanip>

using namespace std;

const int mod = 1000 * 1000 * 1000;

struct node {
    int x, y;
    node *l, *r;
    node(int new_x, int new_y) {
        x = new_x; y = new_y;
        l = NULL; r = NULL;
    }
};

typedef node * pnode;

void merge(pnode &t, pnode l, pnode r) {
    if (l == NULL) 
        t = r;
    else if (r == NULL) 
        t = l;
    else if (l->y > r->y) {
        merge(l->r, l->r, r); 
        t = l;
    }
    else {
        merge(r->l, l, r->l); 
        t = r;
    }
}

void split(pnode t, int x, pnode &l, pnode &r) {
    if (t == NULL) 
        l = r = NULL;
    else if (t->x > x) {
        split(t->l, x, l, t->l); 
        r = t;
    }
    else {
        split(t->r, x, t->r, r); 
        l = t;
    }
}

void add(pnode &t, pnode a) {
    if (t == NULL) 
        t = a;
    else if (a->y > t->y) {
        split(t, a->x, a->l, a->r); 
        t = a;
    }
    else {
        if (t->x < a->x) 
            add(t->r, a);
        else 
            add(t->l, a);
    }
}

int next(pnode t, int x) {
    int ans = -1;
    while (t != NULL) {
        if (t->x < x) 
            t = t->r;
        else {
            if (ans == -1 || ans > t->x) 
                ans = t->x;
            t = t->l;
        }
    }
    return ans;
}

int n, ans, x;
char qt, prev_qt;
pnode root = NULL, num;

int main() {
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);

    scanf("%d\n", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%c %d\n", &qt, &x);
        if (qt == '+') {
            if (prev_qt == '?') 
                x = (x + ans) % mod;
            num = new node(x, rand());
            add(root, num);
        }
        else {
            ans = next(root, x);
            printf("%d\n", ans);
        }
        prev_qt = qt;
    }

    return 0;
}
