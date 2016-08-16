#include <bits/stdc++.h>

using namespace std;

#define boost ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define max(a,b) ((a)>(b)?(a):(b))

typedef long long ll;

int main(){
    boost;
    ll N,i,j,K,L,R,_max;
    string A,B;
    ll Z[1000001];
    cin >> N ;
    cin >> A >> B;
    L = 0 , R = 0;
    for(i = 0 ; i < N ; i++){
        if(i == 0){
            while(R < N && B[R-L] == A[R-L])
                R++;
            Z[0] = (R-L);
            R--;
            _max = Z[0];
            continue;
        }
        if(i > R){
            L = R = i;
            while(R < N && B[R] == A[R-L])
                R++;
            Z[i] = (R-L);
            R--;
            _max = max(_max,Z[i]);
        }else{
            ll K = i-L;
            if(Z[K] < R-i+1)
                Z[i] = Z[K];
            else{
                L = i;
                while(R < N && B[R] == A[R-L])
                    R++;
                Z[i] = R-i;
                R--;
            }
            _max = max(_max,Z[i]);
            }
    }
    for(i = 0 ; i < N ; i++){
        if(Z[i] == _max)
            break;
    }
   /* for(i = 0 ; i < N ; i++)
        cout << Z[i] <<" ";*/
    cout << i <<endl;
}
