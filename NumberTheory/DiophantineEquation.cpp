/************************************************************************************

	Solving Diophantine equations in form of a * x + b * y = c

	Uses extended Euclid algorithm 
	(which finds such x, y that a * x + b * y = gcd(a, b))

	Based on problem 4188 from informatics.mccme.ru
	http://informatics.mccme.ru/moodle/mod/statements/view3.php?chapterid=4188

************************************************************************************/

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

long long gcd(long long a, long long b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

// Finds such x and y, that a * x + b * y = gcd(a, b)
long long extended_gcd(long long a, long long b, long long &x, long long &y) {
	if (b == 0) {
		x = 1; y = 0; 
		return a;
	}
	long long x1, y1;
	long long g = extended_gcd(b, a % b, x1, y1);
	x = y1;
	y = x1 - (a / b) * y1;
	return g;
}

// Solves equation a * x + b * y = c, writes answer to x and y
void solveDiophantine(long long a, long long b, long long c, long long &x, long long &y) {
	long long g = extended_gcd(a, b, x, y);

	if (c % g != 0) {
		puts("Impossible");
		exit(0);
	}

	c /= g;

	x = x * c; y = y * c;
}

long long a, b, c;
long long x, y;
long long g;

int main() {
	//assert(freopen("input.txt","r",stdin));
	//assert(freopen("output.txt","w",stdout));

	cin >> a >> b >> c;

	// Find any solution
	solveDiophantine(a, b, c, x, y);

	// In this problem we search for solution with minimum x >= 0
	// a * x + b * y = gcd(a, b)
	// now for any integer k: a * (x + k * b / g) + b * (y - k * a / g) = gcd(a, b)

	g = gcd(a, b);

	long long add = b / g;
	long long num = 0;
	if (add < 0) 
		num = (long long) floor(1.0 * -x / add);
	else
		num = (long long) ceil(1.0 * -x / add);

	x = x + b / g * num;
	y = y - a / g * num;

	cout << x << " " << y;

	return 0;
}