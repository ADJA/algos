#include <bits/stdc++.h>

using namespace std;

typedef long long ll;


struct node{
    int val,size,sum,pre,suf,maxisum,prior;
    node *l,*r;
};

typedef node* pnode;

int sz(pnode t){
    return (t)?t->size:0;
}

void upd_sz(pnode t){
    if(t)   t->size = sz(t->l)+1+sz(t->r);
}

int sum(pnode t){
    return t?t->sum:0;
}

int pre(pnode t){
    return t?t->pre:0;
}

int suf(pnode t){
    return t?t->suf:0;
}

int maxisum(pnode t){
    return t?t->maxisum:INT_MIN;
}



void operation(pnode t){
    if(!t)  return;
    //reset(t);
    t->sum = t->val + sum(t->l) + sum(t->r);
    t->maxisum = max(max(maxisum(t->l),maxisum(t->r)),max(0,suf(t->l))+t->val+max(0,pre(t->r)));
    t->pre = max(pre(t->l),sum(t->l)+t->val+max(0,pre(t->r)));
    t->suf = max(suf(t->r),sum(t->r)+t->val+max(0,suf(t->l)));
    //cout << t->maxisum << endl;
}


void split(pnode t, pnode& l, pnode& r, int pos, int add = 0){
    if(!t)  {l=r=NULL;return;}
    int curr_pos = add+sz(t->l);
    if(curr_pos <= pos){
        split(t->r,t->r,r,pos,curr_pos+1);
        l = t;
    }else{
        split(t->l,l,t->l,pos,add);
        r = t;
    }
    upd_sz(t);
    operation(t);
}



void merge(pnode& t, pnode l, pnode r){
    //cout << "here" << endl;
    if(!l || !r){
        t=l?l:r;
        return;
    }
    if(l->prior > r->prior){
        merge(l->r,l->r,r);
        t = l;
    }else{
        merge(r->l,l,r->l);
        t = r;
    }
    upd_sz(t);
    operation(t);
}


pnode init(int val){
    pnode p = (pnode)malloc(sizeof(node));
    p->val = p->sum = p->maxisum = p->suf = p->pre = val;
    p->l = p->r = NULL;
    srand((unsigned int)time(NULL));
    p->prior = rand()%1000000;
    p->size = 1;
    return p;
}


int range_query(pnode t,int l, int r){
    pnode mid,L,R;
    split(t,L,mid,l-1);
    split(mid,t,R,r-l);
    int ans = t->maxisum;
    merge(mid,L,t);
    merge(t,mid,R);
    return ans;
}


pnode replace(pnode t, int id, int val){
    pnode mid,L,R;
    split(t,L,mid,id-1);
    split(mid,t,R,0);
    t->val = t->sum = t->pre = t->suf = t->maxisum = val;
    merge(mid,L,t);
    merge(t,mid,R);
    return t;
}


pnode erase(pnode t, int pos){
    pnode mid,L,R;
    split(t,L,mid,pos-1);
    split(mid,t,R,0);
    merge(t,L,R);
    return t;
}


pnode insert(pnode t, int pos, int val){
    pnode mid,L,R,n;
    split(t,L,mid,pos-1);
    pnode p = init(val);
    merge(R,L,p);
    merge(n,R,mid);
    return n;
}



char buf1[1<<22];
int pos1;

char nextChar(){
	while (buf1[pos1] <= ' ') ++pos1;
	return buf1[pos1++];
}

int nextInt() {
	while (buf1[pos1] <= ' ') ++pos1;
	bool sign = false;
	if(buf1[pos1] == '-') {
		sign = true;
		++pos1;
	}
	int res = 0;
	while (buf1[pos1] > ' ')
		res = res*10+(buf1[pos1++]&15);
	return sign ? -res : res;
}


char buf2[1<<22];
int pos2;

void writeInt(int x) {
	if(x<0){
		buf2[pos2++]='-';
		x=-x;
	}
	char d[10];
	int c=0;
	while(true){
		d[c++] = x%10 + '0';
		x/=10;
		if(x==0)break;
	}
	while(--c>=0)buf2[pos2++]=d[c];
}

void writeChar(char x) {
	buf2[pos2++]=x;
}


#define boost ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)

int main(){
    boost;
    ios::sync_with_stdio(0);cin.tie(0);
    int T,N,i,j,k;
    pnode t = NULL;
    cin >> N;
    for(i = 0 ; i < N ; i++){
        ll val;
        cin >> val;
        t = insert(t,i,val);
    }
    ll M;
    cin >> M;
    while(M--){
        char c;
        cin >> c;
        if(c == 'I'){
            ll elem,pos;
            cin >> pos >> elem;
            t = insert(t,pos-1,elem);
        }else if(c == 'D'){
            ll pos;
            cin >> pos;
            t = erase(t,pos-1);
        }else if(c == 'R'){
            ll pos,elem;
            cin >> pos >> elem;
            t = replace(t,pos-1,elem);
        }else if(c == 'Q'){
            ll x,y;
            cin >> x >> y;
            int res = range_query(t,x-1,y-1);
            cout << res<<"\n";
        }
    }
}
