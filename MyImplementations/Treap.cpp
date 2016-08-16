#include <bits/stdc++.h>

using namespace std;

#define boost ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)

typedef long long ll;

struct item{
    int key,prior;
    item *l , *r;
    item(){}
    item(int key, int prior):key(key),prior(prior),l(NULL),r(NULL){}
    };

typedef item* pitem;

void split(pitem t ,int key, pitem& l , pitem& r){
    if(!t)
        l=r=NULL;
    if(key < t->key){
        split(t->l,key,l,t->l);
        r = t;
    }else{
        split(t->r,key,t->r,r);
        l = t;
        }
    }

void _insert(pitem& t , pitem it){
    if(!t)
        t=it;
    else if(it->prior > t->prior){
        split(t,it->key,it->l,it->r);
        t = it;
    }else{
        _insert(it->key < t->key ? t->l,t->r,it);
        }
    }

void _merge (pitem & t, pitem l, pitem r) {
	if (! l ||! r)
		t = l? l: r;
	else if (l-> prior> r-> prior)
		_merge (l-> r, l-> r, r), t = l;
	else
		_merge (r-> l, l, r-> l), t = r;
}

void _erase (pitem & t, int key) {
	if (t-> key == key)
		_merge (t, t-> l, t-> r);
	else
		_erase ( key <t-> key ?t-> l: t-> r, key);
}

pitem unite (pitem l, pitem r) {
	if (! l ||! r) return l? l: r;
	if (l-> prior <r-> prior) swap (l, r);
	pitem lt, rt;
	split (r, l-> key, lt, rt);
	l-> l = unite (l-> l, lt);
	l-> r = unite (l-> r, rt);
	return l;
}
    }
