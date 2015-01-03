/**************************************************************************************

    Floyd-Warshall algorithm finding shortest distance between all
    pairs of vertices in graph. Works in O(N^3)

    Based on problem 95 from informatics.mccme.ru
    http://informatics.mccme.ru/mod/statements/view.php?id=218#1

**************************************************************************************/

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

const int MAXN = 55;
const int INF = (int) 1e9;

int n;
int s, t;
int d[MAXN][MAXN];

int main() {
    //assert(freopen("input.txt","r",stdin));
    //assert(freopen("output.txt","w",stdout));
    
    scanf("%d %d %d", &n, &s, &t);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            scanf("%d", &d[i][j]);
            if (d[i][j] == -1)
                d[i][j] = INF;
        }

    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (d[i][k] + d[k][j] < d[i][j])
                    d[i][j] = d[i][k] + d[k][j];

    if (d[s][t] == INF)
        printf("-1\n");
    else
        printf("%d\n", d[s][t]);

    return 0;
}                             