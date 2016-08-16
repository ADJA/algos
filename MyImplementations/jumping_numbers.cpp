#include <bits/stdc++.h>

using namespace std;

#define boost ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)

typedef long long ll;

vector<int> R;

ll temp,L;

void solve(ll len, ll num){
	if(len == 0){
		if(num <= temp)
			cout << num << endl;
		return;
	}
	int i;
	if(len == L){
	for(i = 0 ; i <= R[len] ; i++){
		solve(len-1,i);
	}
	}else{
		for(i = 0 ; i <= 9 ; i++){
			if(abs(i-(num%10))==1 || num == 0){
				solve(len-1,num*10+i);
			}
		}
	}
}

int main(){
	boost;
	ll N,T,i,j,k;
	cin >> N ;
	temp = N;
	while(N > 0){
		R.push_back(N%10);
		N /= 10;
	}
	//cout << R.size() << endl;
	R.resize(R.size()+1);
	//cout << R.size() << endl;
	for(i = R.size()-1 ; i >= 1 ; i--){
		R[i] = R[i-1];
	}
	L = R.size()-1;
	solve(L,0);
}
