#include <bits/stdc++.h>

using namespace std;

#define boost ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b)  ((a)<(b)?(a):(b))

typedef long long ll;

string preprocess(string S){
    int len = S.length();
    if(len == 0)    return "^$";
    int i,j;
    string ret = "^";
    for(i = 0 ; i < len ; i++)
        ret += "#" + S.substr(i,1);
    ret += "#$";
    return ret;
    }

int longest_palindrome(string S){
    string T = preprocess(S);
    int n = T.length();
    int *P = new int[n];
    int i,j,k;
    int C = 0 , R = 0;
    for(i = 1 ; i < n-1 ; i++){
        int i_mirror = 2*C-i;
        P[i] = (R > i) ? min(R-i,P[i_mirror]):0;
        while(T[i+1+P[i]] == T[i-1-P[i]])
            P[i]++;
        if(i+P[i]>R)
        {
            C = i;
            R = i+P[i];
        }
    }
    int maxlen = 0;
    int cen = 0;
    for(i = 1 ; i < n-1 ; i++){
        if(P[i] > maxlen)
            maxlen = P[i];
            cen = i;
    }
    delete[] P;
    return (S[cen]=='#')?maxlen:maxlen+1;
}

int main(){
    boost;
    string str;
    ll N,i,j,k,l,r;
    cin >> N;
    cin >> str;
    cout << longest_palindrome(str)<<endl;
    }
