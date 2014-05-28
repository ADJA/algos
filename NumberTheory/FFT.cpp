/********************************************************************************

	Fast Fourier transformation used to multiply long numbers.
	Fast non-recursive version. O(NlogN).
	Based on problem 317 from E-Olimp: http://www.e-olimp.com.ua/problems/317

********************************************************************************/

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
#include <complex>

using namespace std;

typedef complex<double> comp;
const double pi = acos(-1.0);
const int MAXN = 505000;

int rev[MAXN * 2];

void fft( comp p[], int n, bool invert) {
	int dig = 0;	
	while ((1 << dig) < n)
		dig++;

	for (int i = 0; i < n; i++) {
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (dig - 1));
		if (rev[i] > i)
			swap(p[i], p[rev[i]]);
	}

	for (int len = 2; len <= n; len <<= 1) {
		double angle = 2 * pi / len;
		if (invert)
			angle *= -1;
		comp wgo(cos(angle), sin(angle));
		for (int i = 0; i < n; i += len) {
			comp w(1);
			for (int j = 0; j < (len >> 1); j++) {
				comp a = p[i + j], b = w * p[i + j  + (len >> 1)];
				p[i + j] = a + b;
				p[i + j + (len >> 1)] = a - b;
				w *= wgo;
			}
		}
	}
	if (invert)
		for (int i = 0; i < n; i++)
			p[i] /= n;	
}

comp a[MAXN * 2], b[MAXN * 2];
int ans[MAXN * 2];
int alen, blen, total;

void readPolynom(comp p[], int &len, bool space) {
	string s;
	if (space)
		getline(cin, s, ' ');
	else
		getline(cin, s);
	len = 1;
	while (len < (int) s.length())
		len *= 2;

	memset(p, 0, sizeof(p));

	int pos = 0;
	for (int i = (int) s.length() - 1; i >= 0; i--) {
		comp coeff(s[i] - '0');
		p[pos] = coeff;
		pos++;
	}
}

int main() {
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	readPolynom(a, alen, true);
	readPolynom(b, blen, false);

	total = max(alen, blen);
	total *= 2;

	fft(a, total, false);
	fft(b, total, false);

	for (int i = 0; i < total; i++)
		a[i] = a[i] * b[i];

	fft(a, total, true);

	for (int i = 0; i < total; i++)
		ans[i] = (int) floor(a[i].real() + 0.5);

	int go = 0;
	for (int i = 0; i < total; i++) {
		ans[i] += go;
		go = ans[i] / 10;
		ans[i] %= 10;
	}

	int ans_ind = total - 1;
	while (ans_ind > 0 && ans[ans_ind] == 0)
		ans_ind--;

	for (int i = ans_ind; i >= 0; i--)
		printf("%d", ans[i]);
	printf("\n");

	return 0;
}