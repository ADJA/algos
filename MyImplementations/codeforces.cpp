
#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi  vector<int>
#define pb  push_back
#define mp  make_pair
#define ALL(x) x.begin(),x.end()
#define M(a,x) memset(a,x,sizeof(a))
#define sci(x) scanf("%d",&x);
#define scl(x) scanf("%lld",&x);
#define scs(x) scanf("%s",x);
#define SZ(x) (int)x.size()
#define print(x) printf("%d",x);
#define nl printf("\n")
#define fr first
#define se second
#define printl(x) printf("%lld",x)
#define F(i,a,n) for(int i=a;i<n;i++)
#define INF 100000000000000000LL
#define LL long long

const int N = 1e3+5;
int n,m,q;
bitset<N> X;
struct Node {
  bitset<N> bit;
  Node* left,*right;
  int cnt;
  Node(bitset<N> b , Node* L , Node* R , int c) {
    left = L;
    right = R;
    cnt = c;
    bit = b;
  }
  Node* insert(int x,int y,int i,int j);
  Node* erase(int x,int y,int i,int j);
  Node* flip(int x,int y,int pos);
};
Node* Node :: insert(int x,int y,int i,int j) {
  if( x<= i && i <= y ) {
    if( x == y ) {
      bitset<N> temp = this->bit;
      temp.set(j);
      return new Node(temp,NULL,NULL,temp.count());
    }
    int mid = (x+y)/2;
    Node* L = this->left->insert(x,mid,i,j);
    Node* R = this->right->insert(mid+1,y,i,j);
    return new Node(this->bit,L,R,L->cnt+ R->cnt);
  }
  return this;
}
Node* Node :: erase(int x,int y,int i,int j) {
  if( x<=i && i <= y) {
    if( x == y ) {
      bitset<N> temp = this->bit;
      temp.reset(j);
      return new Node(temp,NULL,NULL,temp.count());
    }
    int mid = (x+y)/2;
    Node* L = this->left->erase(x,mid,i,j);
    Node* R = this->right->erase(mid+1,y,i,j);
    return new Node(this->bit,L,R,L->cnt+ R->cnt);
  }
  return this;
}
Node* Node :: flip(int x,int y,int pos) {
  if( x<= pos && pos <= y) {
    if( x == y ) {
      bitset<N> temp = this->bit;
      temp = temp ^ (X);
      return new Node(temp,NULL,NULL,temp.count());
    }
    int mid = (x+y)/2;
    Node* L = this->left->flip(x,mid,pos);
    Node* R = this->right->flip(mid+1,y,pos);
    return new Node(this->bit,L,R,L->cnt+ R->cnt);
  }
  return this;
}
Node* null = new Node(0,NULL,NULL,0);
Node* root[100005];
int main() {
  null->left = null->right = null;
  root[0] = null;
  sci(n) ; sci(m) ; sci(q) ;
  for(int i = 1; i<= m ; i++) {
    X.set(i);
  }
  for(int i = 1 ; i <= q ; i++) {
    int tp; sci(tp);
    int x,y;
    if( tp == 1) {
      sci(x) ; sci(y);
      root[i] = root[i-1];
      root[i] = root[i]->insert(1,n,x,y);
    }
    else if(tp == 2 ) {
      sci(x) ; sci(y) ;
      root[i] = root[i-1];
      root[i] = root[i]->erase(1,n,x,y);
    }
    else if(tp == 3) {
      sci(x) ;
      root[i] = root[i-1];
      root[i] = root[i]->flip(1,n,x);
    }
    else if(tp == 4){
      sci(x);
      root[i] = root[x];
    }
    printf("%d\n",root[i]->cnt);
  }
}
