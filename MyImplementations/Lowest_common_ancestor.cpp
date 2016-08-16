#include <bits/stdc++.h>

using namespace std;

#define boost ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define LogN 18

typedef long long ll;

int N,T[250000],P[250000][18],depth[250000];
vector<int> adj[250000];

bool comp(pair<int,int> p1 , pair<int,int> p2){
    return p1.first < p2.first;
    }

void process(){
    int i , j;
    for(i = 0 ; i < N ; i++){
        for(j = 0 ; 1<<j < N ; j++)
            P[i][j] = -1;
    }

    for(i = 0 ; i < N ; i++)
        P[i][0] = i;

    for(j = 1 ; 1<<j < N ; j++){
        for(i = 0 ; i < N ; i++){
            if(P[i][j-1]!=-1)
                P[i][j] = P[P[i][j-1]][j-1];
        }
    }
}

int lca(int x , int y){
    int temp,log,i;
    if(depth[y]>depth[x])
        return lca(y,x);
    for(log = 1 ; 1<<log <= depth[y] ; log++);
    log--;

    for(i = log ; i >= 0 ; i--){
        if(depth[x]-(1<<i)>=depth[y])
            x = P[x][i];
    }
    if(x==y)
        return y;
    for(i = log ; i >= 0 ; i--){
        if(P[x][i]!=-1 && P[x][i]!=P[y][i]){
            x = P[x][i];
            y = P[y][i];
        }
    }
    return ((T[x]==-1)?0:T[x]);
    }

void dfs(int v , int pv){
    depth[v] = (pv==-1)?0:(1+depth[pv]);
    T[v] = pv;
    int i ;
    for(i = 0 ; i < adj[v].size() ; i++){
        if(adj[v][i]!=pv)
            dfs(adj[v][i],v);
    }
    }

int dist(int u , int v){
    int x = lca(u,v);
    int dis = depth[u]+depth[v]-2*depth[x];
    return dis;
    }

int main(){
    boost;
    int N,u,v,r,Q,i,j;
    pair<int,int> p[6];
    cin>>N;
    for(i = 0 ; i < N-1 ; i++){
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0,-1);
    process();
    cin >> Q;
    while(Q--){
        cin >> r >> u >> v;
        r--;u--;v--;
        p[0].second = r;
        p[1].second = u;
        p[2].second = v;
        p[3].second = lca(r,u);
        p[4].second = lca(r,v);
        p[5].second = lca(u,v);

        for(i = 0 ; i < 6 ; i++){
            int x = p[i].second;
            //cout << x <<" ";
            p[i].first = dist(x,u)+dist(x,v)+dist(x,r);
            //cout << p[i].first << endl;
        }
        sort(p,p+6,comp);
        cout << (p[0].second)+1 << endl;
        //cout << "here" << endl;
    }
    }
