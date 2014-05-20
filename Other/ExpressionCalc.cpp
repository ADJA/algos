/*****************************************************************

	Calculation of the value of the expression. 
	Uses recursive descent parser. Supports doubles.

	Available operations: 
	+ - / *     Usual meaning
	-			Unary minus
	#			Root (3 # 8 = 2)
	^			Power (2 ^ 3 = 8)
	#			Square root (unary)

	TODO: find a good problem on it

*****************************************************************/

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

string s;
int len;
double ans;
int p;

double exp();
double term();
double interm();
double factor();

double pr1Sign(char c) {
	return (c == '-' || c == '+');
}

double pr2Sign(char c) {
	return (c == '*' || c == '/');
}

double pr3Sign(char c) {
	return (c == '#' || c == '^');
}

double factor() {
	double res = 0.0, dpow = 1.0;
	bool dot = false;
	if (p >= len) {
		return res;
	}
	if (s[p] == '(') {
		p++;
		res = exp();
		p++;
		return res;
	}
	if (s[p] == '-') {
		p++;
		res = interm();
		return -res;
	}
	if (s[p] == '#') {
		p++;
		res = interm(); 
		return pow(res, 0.5);
	}
	while (p < len && ((s[p] >= '0' && s[p] <= '9') || s[p] == '.')) {
		if (s[p] == '.') 
			dot = true;
		else {
			res = res * 10 + s[p] - '0';
			if (dot) 
				dpow *= 10.0;
		}
		p++;
	}
	return res / dpow;
}

double interm() {
	double res, t;
	char c;
	res = factor();
	while (p < len && pr3Sign(s[p])) {
		c = s[p];
		p++;
		t = factor();
		if (c == '^') {
			if (t < 1.0 && t > -1.0 && t != 0 && res < 0)
				res = -pow(-res, t);
			else
				res = pow(res, t);
		}
		if (c == '#') {
			if (t < 0) 
				res = -pow(-t, (1.0 / res));
			else
				res = pow(t, (1.0 / res));
		}
	}
	return res;	
}

double term() {
	double res, t;
	char c;
	res = interm();
	while (p < len && pr2Sign(s[p])) {
		c = s[p];
		p++;
		t = interm();
		if (c == '*') 
			res *= t;
		if (c == '/') 
			res /= t;
	}
	return res;		
}

double exp() {
	double res, t;
	char c;
	res = term();
	while (p < len && pr1Sign(s[p])) {
		c = s[p];
		p++;
		t = term();
		if (c == '-') 
			res -= t;
		if (c == '+')
			res += t;
	}
	return res;
}

void remove_whitespaces(string &s) {
	string temp = s;
	s = "";

	for (int i = 0; i < (int) temp.length(); i++)
		if (temp[i] != ' ')
			s.append(1, temp[i]);
}

int main() {
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);

	getline(cin,s);
	remove_whitespaces(s);

	len = s.length();

	ans = exp();
	printf("%lg",ans);

	return 0;
}