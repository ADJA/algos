/*******************************************************************************************************

    Centroid decomposition in O(NlogN), and LCA in O(logN).

    More about centroid decomposition:
     - http://acm.math.spbu.ru/~sk1/mm/lections/zksh2016-centroid/conspect.pdf (in Russian)
     - https://medium.com/carpanese/an-illustrated-introduction-to-centroid-decomposition-8c1989d53308

    Based on problem Xenia and Tree: https://codeforces.com/contest/342/problem/E
    Total time complexity of the code below is O(Nlog^2N).

********************************************************************************************************/

#include <bits/stdc++.h>

using namespace std;

#define sz(x) (int) x.size()
#define all(a) a.begin(), a.end()

const int MAXN = 105000;
const int INF = 1e9;

int n, m;
vector<int> g[MAXN];
int sz[MAXN];
int depth[MAXN];
int par[MAXN][20];

int level[MAXN];
bool isCenter[MAXN];
int centPar[MAXN];

int distToRed[MAXN];

void dfs(int v, int d, int p = 0) {
    depth[v] = d;

    par[v][0] = p;
    for (int i = 1; i < 20; i++)
        par[v][i] = par[par[v][i - 1]][i - 1];

    for (int to : g[v])
        if (to != p)
            dfs(to, d + 1, v);
}

int lca(int a, int b) {
    if (depth[a] < depth[b])
        swap(a, b);
    for (int i = 19; i >= 0; i--)
        if (depth[par[a][i]] >= depth[b])
            a = par[a][i];
    if (a == b)
        return a;
    for (int i = 19; i >= 0; i--)
        if (par[a][i] != par[b][i]) {
            a = par[a][i];
            b = par[b][i];
        }
    return par[a][0];
}

int dist(int a, int b) {
    int lc = lca(a, b);
    return depth[a] + depth[b] - 2 * depth[lc];
}

int findCentroid(int v, int compSz, int p = -1) {
    for (int to : g[v])
        if (!isCenter[to] && to != p) {
            if (sz[to] > compSz / 2)
                return findCentroid(to, compSz, v);
        }
    return v;
}

int calcSz(int v, int p = -1) {
    sz[v] = 1;
    for (int to : g[v])
        if (!isCenter[to] && to != p)
            sz[v] += calcSz(to, v);
    return sz[v];
}

void centroids(int v, int lv, int prev = -1) {
    calcSz(v);

    int center = findCentroid(v, sz[v]);
    isCenter[center] = true;
    centPar[center] = prev;
    level[center] = lv;

    for (int to : g[center])
        if (!isCenter[to])
            centroids(to, lv + 1, center);
}

void paint(int v) {
    int a = v;
    for (int lv = level[v]; lv >= 0; lv--) {
        distToRed[a] = min(distToRed[a], dist(a, v));
        a = centPar[a];
    }
}

int get(int v) {
    int res = INF;
    int a = v;
    for (int lv = level[v]; lv >= 0; lv--) {
        res = min(res, distToRed[a] + dist(a, v));
        a = centPar[a];
    }
    return res;
}

int main() {

    scanf("%d %d", &n, &m);
    for (int i = 0; i < n - 1; i++) {
        int from, to;
        scanf("%d %d", &from, &to);
        from--; to--;
        g[from].push_back(to);
        g[to].push_back(from);
    }

    dfs(0, 0);
    centroids(0, 0);

    for (int i = 0; i < n; i++)
        distToRed[i] = INF;

    paint(0);

    for (int i = 0; i < m; i++) {
        int t, v;
        scanf("%d %d", &t, &v);
        v--;
        if (t == 1) 
            paint(v);
        else
            printf("%d\n", get(v));
    }

    return 0;
}
