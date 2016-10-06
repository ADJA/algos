#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define boost ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)

struct node{
    ll val,prior,size;
    node *l,*r;
};

typedef node* pnode;

ll sz(pnode t){
    return (t)?t->size:0;
}

void upd_sz(pnode t){
    if(t)   t->size = sz(t->l)+1+sz(t->r);
}



void split(pnode t, pnode&l , pnode& r, ll key){
    if(!t)  {l=r=NULL;return;}
    if(key >= t->val){
        split(t->r,t->r,r,key);
        l = t;
    }
    else if(key < t->val){
        split(t->l,l,t->l,key);
        r = t;
    }
    upd_sz(t);
}

void merge(pnode& t, pnode l , pnode r){
    if(!l || !r)    {t = l?l:r;return;}
    if(l -> prior > r-> prior){
        merge(l->r,l->r,r);
        t = l;
    }else{
        merge(r->l,r->l,l);
        t = r;
    }
    upd_sz(t);
}


void insert(pnode& t, pnode it){
    //cout << it->prior << endl;
    if(!t)  {t = it;return;}
    if(it->prior > t->prior){
        split(t,it->l,it->r,it->val);
        t = it;
    }else{
        insert(t->val <= it->val ? t->r:t->l,it);
    }
    upd_sz(it);
}


void erase(pnode& t, ll key){
    if(!t)  return;
    if(t->val == key){
        pnode temp = t;
        merge(t,t->l,t->r);
        free(temp);
    }else{
        erase(key >= t->val ? t->r: t->l,key);
    }
    upd_sz(t);
}


pnode init(ll val){
    pnode ret = (pnode)malloc(sizeof(node));
    ret->val = val;
    srand((unsigned int)time(NULL));
    ret->prior = rand();
    ret->size = 1;
    ret->l = ret->r = NULL;
}


ll givecount(pnode t, ll v){
    if(!t)  return 0;
    if(v > t->val){
        return sz(t->l)+1+givecount(t->r,v);
    }else{
        if(v == t->val)
            return sz(t->l)+1;
        else{
            return givecount(t->l,v);
        }
    }
}


pnode find(pnode t, ll key){
    if(!t)  return NULL ;
    if(t->val == key)   return t;
    if(key < t->val)    return find(t->l,key);
    else    return find(t->r,key);
}

ll Kquery(pnode t, ll k){
    ll count = sz(t->l);
    if(count + 1 == k)
    	return t->val;
    if(k < count+1)
        return Kquery(t->l,k);
    else
        return Kquery(t->r,k-count-1);
}


int main(){
    boost;
    ll T,N,i,j,k;
    pnode t = NULL;
    ll C;
    cin >> C;
    while(C--){
        char c;
        ll val;
        cin >> c;
        if(c == 'I'){
            cin >> val;
            pnode n = init(val);
            if(find(t,val)==NULL)
                insert(t,n);
        }else if(c == 'D'){
            cin >> val;
            erase(t,val);
        }else if(c == 'C'){
            cin >> val;
            cout << givecount(t,val) << endl;
        }else if(c == 'K'){
            cin >> val;
            if(val > sz(t))
                cout << "invalid" << endl;
            else
                cout << Kquery(t,val) << endl;
        }
    }
}
