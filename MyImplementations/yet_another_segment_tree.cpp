#include <bits/stdc++.h>

using namespace std;

#define boost ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)

typedef long long ll;
const int mx = 100010;

int a[mx+1];
vector<int> queryrange;

struct node{
    unordered_map<int , int> CountOccurence;
    int dominant;
}SegmentTree[4*mx];

void build(int r, int start , int _end){
    if(start == _end){
        SegmentTree[r].CountOccurence.clear();
        SegmentTree[r].CountOccurence[a[start]] += 1;
        SegmentTree[r].dominant = a[start];
        return;
    }
    int mid = (start+_end)>>1;
    build(2*r,mid+1,_end);
    build(2*r+1,start,mid);
    int length = (_end-start+1);
    SegmentTree[r].CountOccurence.clear();
    std::unordered_map<int,int>::iterator it = SegmentTree[2*r].CountOccurence.begin();
    while(it != SegmentTree[2*r].CountOccurence.end()){
        SegmentTree[r].CountOccurence[it->first] += it->second;
        it++;
    }
    it = SegmentTree[2*r+1].CountOccurence.begin();
    while(it != SegmentTree[2*r+1].CountOccurence.end()){
        SegmentTree[r].CountOccurence[it->first] += it->second;
        it++;
    }
    if(SegmentTree[r].CountOccurence[SegmentTree[2*r].dominant] > (length/2)){
        SegmentTree[r].dominant = SegmentTree[2*r].dominant;
    }else if(SegmentTree[r].CountOccurence[SegmentTree[2*r+1].dominant] > (length/2)){
        SegmentTree[r].dominant = SegmentTree[2*r+1].dominant;
    }else{
        SegmentTree[r].dominant = -1;
    }
    return;
    }

void update(int x , int y , int r ,int idx , int val , int oldval){
    if(idx < x || idx > y)
        return;
    if(x == y){
        SegmentTree[r].CountOccurence.clear();
        a[idx] = val;
        SegmentTree[r].CountOccurence[a[idx]] += 1;
        SegmentTree[r].dominant = a[idx];
        return;
    }
    int mid = (x+y)>>1;
    update(x,mid,2*r,idx,val,oldval);
    update(mid+1,y,2*r+1,idx,val,oldval);
    int length = (y-x+1);
    SegmentTree[r].CountOccurence[val] += 1;
    SegmentTree[r].CountOccurence[oldval] -= 1;
     if(SegmentTree[r].CountOccurence[SegmentTree[2*r].dominant] > (length/2)){
        SegmentTree[r].dominant = SegmentTree[2*r].dominant;
    }else if(SegmentTree[r].CountOccurence[SegmentTree[2*r+1].dominant] > (length/2)){
        SegmentTree[r].dominant = SegmentTree[2*r+1].dominant;
    }else{
        SegmentTree[r].dominant = -1;
    }
    return;
}

void query(int x , int y , int r, int qs , int qe){
    if(qs < x || qe > y)
        return;
    if(qs >= x && qe <= y){
        queryrange.push_back(r);
        return;
    }
        int mid = (x+y)>>1;
        query(x,mid,2*r,qs,qe);
        query(mid+1,y,2*r+1,qs,qe);
    }

int main(){
    boost;
    ll n,q;
    ll i,j,k;
    for(i = 1 ; i <= n ; i++)
        cin >> a[i];
    build(1,1,n);
    while(q--){
        ll type;
        cin >> type;
        switch(type){
        case 1:
            int idx,val;
            cin >> idx >> val;
            update(1,n,1,idx,val,a[idx]);
            break;
        case 2:
            int qs,qe,found = 0,length;
            cin >> qs >> qe;
            length = qe-qs+1;
            queryrange.clear();
            query(1,n,1,qs,qe);
            for(i = 0 ; i < queryrange.size() ; i++){
                int count = 0;
                for(j = 0 ; j < queryrange.size() ; j++){
                    count += SegmentTree[queryrange[j]].CountOccurence[SegmentTree[i].dominant];
                }
                if(count > (length/2)){
                    found = 1;
                    break;
                }
            }
            if(found == 1){
                cout << "Yes\n";
            }else{
                cout << "No\n";
                }
            break;
            }
    }
    }
