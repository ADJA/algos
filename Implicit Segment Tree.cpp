// Implicit segment tree ,   support  range update [L-R] and point query.
 
// Also handle queries when  intitially array is emmpty ,  and 1 <= L , R <= 1e9
 
#include<bits/stdc++.h>
#define ll long long
 
using namespace std;
 
struct Implicit_segment_tree {
    ll Sum;
	Implicit_segment_tree *left , *right;
    Implicit_segment_tree(ll _Sum , Implicit_segment_tree *_left , Implicit_segment_tree *_right ){
    Sum = _Sum;
    left = _left;
    right = _right;
    }
};
 
void update(Implicit_segment_tree *root , int l , int r , int s , int e , ll value ){
       if(s > r || l > e )
           return;
         if(l >= s && r <= e ){
            root->Sum += value;
            return;
         }
         if(root->left == NULL)
         root->left = new Implicit_segment_tree(0 , NULL , NULL);
         if(root->right == NULL)
         root->right = new Implicit_segment_tree(0 , NULL , NULL);
         update(root->left , l , (l + r)/2 , s , e , value );
         update(root->right , (l + r)/2 + 1 , r , s, e , value);
}
 
ll query(Implicit_segment_tree *root , int l , int r, int idx) {
	 if( root == NULL ||  idx > r || l > idx )
	  return 0;
	  if( l  == r )
	  return root->Sum;
	return root->Sum + query(root->left , l , ( l + r)/2 , idx) + query( root->right , (l + r)/2 + 1 , r, idx);
}
 
 
int main() {
                  int N , Q;
                    scanf("%d%d",&N,&Q);
                      Implicit_segment_tree *root = new Implicit_segment_tree(0 , NULL, NULL);
                      for(int i = 1 ; i <= N ; ++i ){
                              int x;
                              scanf("%d",&x);
                                update(root , 1 , N , i , i , x );
                     }
                     while(Q--){
                        int choice;
                         scanf("%d",&choice);                     // choice 1  for update , 2 for query at index x
                        if(choice == 1){
                            int L , R , value;
                            scanf("%d%d%d",&L,&R,&value);
                              update(root, 1 , N , L , R , value );
                        } else {
                                      int idx;
                          scanf("%d",&idx);
                            printf("%lld\n",query(root, 1 , N , idx));
                        }
                     }
    return 0;
}
