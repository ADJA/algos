#include <bits/stdc++.h>

using namespace std;

#define boost ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)

typedef long long ll;

ll dp[19][512][2520][2];
vector<int> digits;
int K;

int check(int mask , int mod){
    int i,j,temp = 0;
    for(i = 1 ; i <= 9 ; i++){
        if((mask & (1<<(i-1))) && mod%i == 0)
            temp++;
    }
    if(temp >= K)
        return 1;
    return 0;
}

ll solve(int len , int mask , int mod , int l){
    int i,j,k;
     if(dp[len][mask][mod][l]!=-1){
            //cout << "here" << endl;
            return dp[len][mask][mod][l];
        }

    if(len == 0){
        return check(mask,mod);
    }
    ll ans = 0;
    if(l==0){
        for(i = 0 ; i <= 9 ; i++){
            if(i == 0)
                ans += solve(len-1,mask,(mod*10+i)%2520,0);
            else
                ans += solve(len-1,mask|(1<<(i-1)),(mod*10+i)%2520,0);
        }
    }else{
        for(i = 0 ; i <= digits[len]; i++){
            if(i < digits[len]){
                if(i == 0)
                ans += solve(len-1,mask,(mod*10+i)%2520,0);
            else
                ans += solve(len-1,mask|(1<<(i-1)),(mod*10+i)%2520,0);
            }else{
                if(i == 0)
                ans += solve(len-1,mask,(mod*10+i)%2520,1);
            else
                ans += solve(len-1,mask|(1<<(i-1)),(mod*10+i)%2520,1);
                }
        }
        }
    return dp[len][mask][mod][l] = ans;
    }

int main(){
    boost;
    ll i,j,k,Q,l,r;
    cin >> Q;
    while(Q--){
        ll ans;
        digits.clear();
        cin >> l >> r >> K;
        memset(dp,-1,sizeof(dp));
        l--;
        while(l>0){
            digits.push_back(l%10);
            l/=10;
        }
        digits.push_back(0);
        for(i = digits.size()-1 ; i >= 1 ; i--)
            digits[i] = digits[i-1];
        ll ans1 = solve(digits.size()-1,0,0,1);
        //cout << ans1 << endl;
        digits.clear();
        memset(dp,-1,sizeof(dp));
        while(r>0){
            digits.push_back(r%10);
            r/=10;
        }
        digits.push_back(0);
        for(i = digits.size()-1 ; i >= 1 ; i--)
            digits[i] = digits[i-1];
        ll ans2 = solve(digits.size()-1,0,0,1);
        //cout << ans2 << endl;
        cout << ans2-ans1 << endl;
    }
    }
