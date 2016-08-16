#include <bits/stdc++.h>

using namespace std;
#define boost ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define INF 1000000007

typedef long long ll;

int cost[501][501];//cost matrix
int n,max_match = 0;//n workers and n jobs
int lx[501],ly[501];//label matrix for x and y part
int xy[501],yx[501];//vertex that matches with x and vertex that matches with y
bool S[501],T[501];//S and T set in algorithm
int slack[501];//as described in algorithm
int slackx[501];//such that l(slackx[y])+l[y]-w(slackx[y],y) = slack[y];
int prev[501]; //memorizing the alternating path

void init_labels(){
    memset(lx,0,sizeof(lx));
    memset(ly,0,sizeof(ly));
    int i,j;
    for(i = 0 ; i < n ; i++){
        for(j = 0 ; j < n ; j++)
            lx[i] = max(lx[i],cost[i][j]);
    }
    }

void update_labels(){
    ll x,y,delta = INF;
    for(y = 0 ; y < n ; y++){
        if(!T[y])
            delta = min(delta,slack[y]);
    }
    for(x = 0 ; x < n ; x++){
        if(S[x])
            lx[x] -= delta;
    }
    for(y = 0 ; y < n ; y++){
        if(T[y])
            ly[y] += delta;
    }
    for(y = 0 ; y < n ; y++){
        if(!T[y])
            slack[y] -= delta;
    }
    }

void add_to_tree(int x , int prevx){
    S[x] = true;
    prev[x] = prevx;
    for(int y = 0 ; y < n ; y++){
        if(lx[x] + ly[y] - cost[x][y]<slack[y]){
            slack[y] = lx[x] + ly[y] - cost[x][y];
            slackx[y] = x;
        }
    }
    }


void augment(){ //main function of the algorithm
    if(n == max_match)  return;//perfect matching
    int x,y,root; // just counters and root vertex
    int q[501],wr = 0, rd = 0; // just for bfs , read and write
    memset(S,false,sizeof(S));
    memset(T,false,sizeof(T));
    memset(prev,-1,sizeof(prev));
    for(x = 0 ; x < n ; x++){
        if(xy[x] == -1){
            q[wr++] = root = x;
            S[x] = true;
            prev[x] = -2;
            break;
        }
    }
    for(y = 0 ; y < n ; y++){
        slack[y] = lx[root]+lx[y]-cost[root][y];
        slackx[y] = root;
    }
    while(true){
        while(rd < wr){
            x = q[rd++];
            for(y = 0 ; y < n ; y++){
                if(lx[x] + ly[y] == cost[x][y] && !T[y])
                {
                    if(yx[y] == -1) break;
                    T[y] = true;
                    q[wr++] = yx[y];
                    add_to_tree(yx[y],x);
                }
            }
            if(y < n)   break;
        }
        if(y < n)   break;
        update_labels();
        wr = rd = 0;
        for(y = 0 ; y < n ; y++){
            if(!T[y] && slack[y] == 0){
                if(yx[y] == -1){
                    x = slackx[y];
                    break;
                }else{
                    T[y] = true;
                    if(!S[yx[y]]){
                        q[wr++] = yx[y];
                        add_to_tree(yx[y],slackx[y]);
                    }
                }
            }
        }
        if(y < n) break;
    }
    if(y < n){
        max_match++; //increment matching
        //in this cycle we inverse edges along augmenting path
        for (int cx = x, cy = y, ty; cx != -2; cx = prev[cx], cy = ty){
                ty = xy[cx];
                yx[cy] = cx;
                xy[cx] = cy;
            }
        augment(); //recall function, go to step 1 of the algorithm
    }
}

int main(){
    ll K,i,j,R,C;
    memset(cost,0,sizeof(0));
    memset(xy,-1,sizeof(xy));
    memset(yx,-1,sizeof(yx));
    init_labels();
    cin >> n >> K;
    for(i = 0 ; i < K ; i++){
        cin >> R >> C;
        R--;C--;
        cost[R][C] = 1;
    }
    augment();
    int cost = 0;
    for(i = 0 ; i < n ; i++){
        cost += (lx[i]+ly[i]);
    }
    //cout << max_match << endl;
    cout << cost << endl;
    }
