/*******************************************************************************

    Matrix multiplication and fast binary power.
    Works in O(n ^ 3).

    Based on problem Walk from AtCoder:
    https://atcoder.jp/contests/dp/tasks/dp_r

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

#define sz(x) (int) x.size()
#define unique(x) x.erase(unique(x.begin(), x.end()), x.end())
#define all(a) a.begin(), a.end()
#define sqr(x) ((x) * (x)) 
#define y1 aksjdaskdjksjfksdjf
#define left kdnvldvoiwejifejg
#define right lkdsjflksdjfdjfk
#define prev asdasfsadjkjsdfjs

const int MAXN = 55;
const int mod = (int) 1e9 + 7;

class Matrix {
public:
    int a[MAXN][MAXN];
    int n, m;

    Matrix() {}

    Matrix(int n, int m, int a[MAXN][MAXN]) {
        init(n, m, a);
    }

    void init(int n, int m, int a[MAXN][MAXN]) {
        this->n = n; this->m = m;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                this->a[i][j] = a[i][j];
            }
        }
    }

    static Matrix identity(int n) {
        int res[MAXN][MAXN];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    res[i][j] = 1;
                } else {
                    res[i][j] = 0;
                }
            }
        }
        return Matrix(n, n, res);
    }

    static Matrix mul(Matrix a, Matrix b) {
        assert(a.m == b.n);
        int res[MAXN][MAXN];
        for (int i = 0; i < a.n; i++) {
            for (int j = 0; j < b.m; j++) {
                res[i][j] = 0;
                for (int k = 0; k < a.m; k++) {
                    res[i][j] = (res[i][j] + 1ll * a.a[i][k] * b.a[k][j] % mod) % mod;
                }
            }
        }
        return Matrix(a.n, b.m, res);
    }
};

Matrix binPow(Matrix m, long long p) {
    Matrix result = Matrix::identity(m.n);
    while (p) {
        if (p & 1) {
            result = Matrix::mul(result, m);
            p--;
        } else {
            m = Matrix::mul(m, m);
            p /= 2;
        }
    }
    return result;
}

int n;
long long len;
int a[MAXN][MAXN];
int col[MAXN][MAXN];
Matrix mat;

int main() { 

    scanf("%d %lld", &n, &len);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[j][i]);
        }
    }

    mat = Matrix(n, n, a);
    mat = binPow(mat, len);

    for (int i = 0; i < n; i++) {
        col[i][0] = 1;
    }
    Matrix colMat = Matrix(n, 1, col);
    colMat = Matrix::mul(mat, colMat);

    int res = 0;
    for (int i = 0; i < n; i++) {
        res = (res + colMat.a[i][0]) % mod;
    }

    cout << res << endl;

    return 0;
}
