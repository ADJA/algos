#include <bits/stdc++.h>

using namespace std;

#define boost ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define max(a,b) ((a)>(b)?(a):(b))

typedef long long ll;

struct TrieNode{
    ll val;
    struct TrieNode* arr[2];
public:
    TrieNode(){
        val = 0;
        arr[0] = NULL;
        arr[1] = NULL;
        }
    };
typedef struct TrieNode node;

node* NewNode(){
    node *n = new node;
    }

void _insert(node *root, ll pre_sum){
    node *temp = root;
    int i;
    for(i = 31 ; i >= 0 ; i--){
        int va = 1 & (pre_sum << i);
        if(temp -> arr[va] == NULL)
            temp -> arr[va] = NewNode();
        temp = temp -> arr[va];
    }
    temp -> val = pre_sum;
}

ll query(node *root , ll pre){
    node *temp = root;
    int i;
    for(i = 31 ; i >= 0 ; i--){
        int va = 1 & (pre << i);
        if(temp -> arr[1-va] != NULL)
            temp = temp -> arr[1-va];
        else if(temp -> arr[va] != NULL)
            temp = temp -> arr[va];
    }
    return pre^(temp->val);
    }

int main(){
    ll T,N,arr[100001],i,j;
    cin >> T;
    while(T--){
    ll presum = 0 ,result = 0;
    ll _max = INT_MIN;
    cin >> N;
    node *root = NewNode();
    _insert(root,0);
    for(i = 0 ; i < N ; i++){
        cin >> arr[i];
        presum = presum ^ arr[i];
        _insert(root,presum);
        _max = max(_max,query(root,presum));
    }
    cout << _max << endl;
    }
    }
