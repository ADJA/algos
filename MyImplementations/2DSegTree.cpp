 
#include<iostream>
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>
#define NL cout << "\n";
using namespace std;
 
const int maxn = 5e2 + 5;
 
int a[maxn][maxn], st[maxn*4][maxn*4] , n , m;
 
void printGrid(){
 
	cout << " this is our initial grid " << endl;
 
	for(int i = 0 ; i < n ; i++){
		for(int j = 0 ; j < m ; j++){
			cout << a[i][j] << " " ;
		}
		cout << endl;
	}
 
}
 
int generateGrid(){
 
	n = 4 , m = 4;
	// n rows , m columns
	for(int i = 0 ; i < n ; i++)
		for(int j = 0 ; j < m ; j++)
			a[i][j] = rand()%10;
 
	printGrid();
 
}
 
// here we are not changing first 3 arguments, 
// means, our rows are fixed, 
// we narrow down to our columns, and generate segment tree for row [r1 , r2] (including)
// we can pass flag instead of passing two parameters r1, and r2(that's just optimisation)
 
void genSegTreeFrom_c1_to_c2(int parSegTree , int r1 , int r2 ,int ind , int c1 , int c2){
 
	if(c1 == c2){
 
		if(r1 == r2){
			// means we are working on single row, 
			// and we can directly generate segment tree for that row = r1;
			st[parSegTree][ind] = a[r1][c1];
			return;
		}
 
		// here parSegTree = parent seg tree,
		// (parSegTree<<1) + 1) is left child seg tree
		// (parSegTree<<1) + 2) is right child seg tree
		// we will build par seg tree using values of children seg trees
 
		// we are creating seg tree which contains sum from row (r1 to r2)
 
		if(r1 != r2){
			st[parSegTree][ind] = st[(parSegTree<<1)+1][ind] + st[(parSegTree<<1)+2][ind];
			return;
		}
 
	}
 
	int mid = (c1 + c2)>>1;
	genSegTreeFrom_c1_to_c2(parSegTree, r1, r2, (ind<<1)+1,   c1 , mid );
	genSegTreeFrom_c1_to_c2(parSegTree, r1, r2, (ind<<1)+2, mid+1, c2  );
	st[parSegTree][(ind)] = (st[parSegTree][(ind<<1)+1] + st[parSegTree][(ind<<1)+2]);
 
	return;
 
}
 
void genSegTreeFrom_r1_to_r2(int ind , int r1 , int r2){
 
	cout << " came to generate seg tree for row " << r1 << " to " << r2 << endl;
	// if we have narrow down to single row
	if(r1==r2){
		genSegTreeFrom_c1_to_c2(ind,r1,r2,0,0,m-1);
		return;
	}
 
	int mid = (r1+r2)>>1;
	cout << " going to generate segTree for " << r1 << " to " << mid << endl;
	genSegTreeFrom_r1_to_r2((ind<<1)+1, r1 , mid);
	cout << " going to generate segTree for " << mid+1 << " to " << r2 << endl;
	genSegTreeFrom_r1_to_r2((ind<<1)+2, mid+1, r2);
 
	// now using upper two seg trees, we create new seg tree
	genSegTreeFrom_c1_to_c2(ind,r1,r2,0,0,m-1);
 
}
 
void generate2D_segTrees(){
 
	parseRow(0,0,n-1);
 
}
 
void print2(int segTreeNum , int ind , int c1 , int c2){
 
	if(c1 == c2){
		cout << " sum from col " << c1 << " to " << c2 << " is " << st[segTreeNum][ind] << endl;
		return;
	}
 
	int mid = (c1 + c2)>>1;
 
	print2(segTreeNum , (ind<<1) + 1 , c1 , mid);
	print2(segTreeNum , (ind<<1) + 2 , mid+1 , c2);
	cout << " sum from col " << c1 << " to " << c2 << " is " << st[segTreeNum][ind] << endl;
 
}
 
void print1(int ind , int r1 , int r2){
 
	if(r1 == r2){
		cout << " printing semgnet tree for sum of rows from " << r1 << " to " << r2 << endl;
		print2(ind,0,0,m-1);
		NL NL NL NL NL
		return;
	}
 
	int mid = (r1+r2)>>1;
	print1((ind<<1)+1,r1,mid);
	print1((ind<<1)+2,mid+1,r2);
 
	cout << " printing semgnet tree for sum of rows from " << r1 << " to " << r2 << endl;
	print2(ind,0,0,m-1);
	NL NL NL NL NL
 
}
 
void print2D_segTrees(){
 
	print1(0,0,n-1);
 
}
 
// for getSum, try to write function yourself, we will upload code in 2 days :) 
 
void getSum(){
 
 
 
}
 
// for update try to write function yourself, we will upload code in 2 days : ) 
void update(){
 
 
}
signed main(){
 
    //OPTIMIZE
 
    //freopen("in.txt" , "r" , stdin) ;
    //freopen("out.txt" , "w" , stdout) ;
 
    int t=1;
    //cin >> t;
    while(t--)
        generateGrid() , generate2D_segTrees() , print2D_segTrees();
 
	return 0;
 
}
