#include <bits/stdc++.h>

#define boost ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define INF 786433

typedef long long ll;

using namespace std;

const int mod = 786433;
const int root = 10;
const int root_pw = (1<<18);

inline int mul(int a, int b, int m = INF) {return (int)(((ll)a * (ll)b) % m);}


ll pow(ll a, ll b , ll mod){
    ll x = 1,y = a;
    while(b > 0){
        if(b%2)
            x = (x * y)%mod;
        y = (y * y)%mod;
        b /= 2;
    }
    return x%mod;
}

void fft(vector<int> & a) {
	int n = (int) a.size();

	for (int i=1, j=0; i<n; ++i) {
		int bit = n >> 1;
		for (; j>=bit; bit>>=1)
			j -= bit;
		j += bit;
		if (i < j)
			swap (a[i], a[j]);
	}

	for (int len=2; len<=n; len<<=1) {
		int wlen = 1000;
		for (int i=len; i<root_pw; i<<=1)
			wlen = int (wlen * 1ll * wlen % mod);
		for (int i=0; i<n; i+=len) {
			int w = 1;
			for (int j=0; j<len/2; ++j) {
				int u = a[i+j],  v = int (a[i+j+len/2] * 1ll * w % mod);
				a[i+j] = u+v < mod ? u+v : u+v-mod;
				a[i+j+len/2] = u-v >= 0 ? u-v : u-v+mod;
				w = int (w * 1ll * wlen % mod);
			}
		}
	}
}


int main(){
    boost;
    ll N,i,j;
    vector<int> a(1<<18,0),ans(mod,-1);
    vector<int> temp = a;
    cin >> N;
    for(i = 0 ; i <= N ; i++)
        cin >> a[i];
    ans[0] = a[0];
    fft(a);
    int p = 1;
    for(i = 0 ; i < root_pw ; i++){
        ans[p] = a[i];
        p = mul(p,1000,mod);
    }
    a = temp;
    p = 10;
    for(i = 1 ; i <= N ; i++){
        a[i] = mul(a[i],p);
        p = mul(p,10,mod);
    }
    fft(a);
    p = 10;
    for(i = 0 ; i < root_pw ; i++){
        ans[p] = a[i];
        p = mul(p,1000,mod);
    }
    a = temp;
    p = 100;
    for(i = 1 ; i <= N ; i++){
        a[i] = mul(a[i],p);
        p = mul(p,100,mod);
    }
    fft(a);
    p = 100;
    for(i = 0 ; i < root_pw ; i++){
        ans[p] = a[i];
        p = mul(p,1000,mod);
    }
    ll q;
    cin >> q;
    while(q--){
        ll x;
        cin >> x;
        cout << ans[x]<<endl;
    }
    }
