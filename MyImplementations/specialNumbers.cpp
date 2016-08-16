#include <bits/stdc++.h>

using namespace std;

#define boost ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)

typedef long long ll;

ll ans;
string str;
ll K;

int check(string s , int d){
	int status = 1;
	ll rem = d;
	ll i;
	if(s.length() == 0){
		if(d%K == 0)
			status = 0;
		return status;
	}
	for(i = s.length()-1 ; i >= 0 ; i--){
		ll num = (int)(s[i]-'0')*pow(10,s.length()-i)+rem;
		if(num % K == 0){
			status = 0;
			break;
		}
		rem = num;
	}
	return status;
}



ll solve(ll len , string R ,int isequal){
	if(len == -1){
		//cout << R << endl;
		return 1;
	}
	if(isequal == 0){
		ll i;
		for(i = 0 ; i <= 9 ; i++){
			if(check(R,i)){
				ans += solve(len-1,R+to_string(i),0);
			}
		}
	}
	else{
		ll i;
		for(i = 0 ; i <= ((int)(str[len]-'0')) ; i++){
			if(i < ((int)(str[len]-'0'))){
				if(check(R,i)){
				ans += solve(len-1,R+to_string(i),0);
			}
			}else{
				if(check(R,i)){
				ans += solve(len-1,R+to_string(i),1);
			}
		}
	}
	}
	return ans;
}

int main(){
	boost;
	ll T,N,i,j,k;
	cin >> T;
	while(T--){
		ll L,R;
		cin >> R >> K;
		L--;
		ans = 0;
		str = to_string(R);
		ll ansr = solve(to_string(R).length()-1,"",1);
		//cout << ansr << endl;
		ans = 0;
		str = to_string(L);
		ll ansl = solve(to_string(L).length()-1,"",1);
		cout<< ansr-ansl << endl;
	}
}
