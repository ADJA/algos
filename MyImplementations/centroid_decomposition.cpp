#include<bits/stdc++.h>
 
using namespace std;
 
typedef pair<int,int>   II;
typedef vector< II >      VII;
typedef vector<int>     VI;
typedef vector< VI > 	VVI;
typedef long long int 	LL;
typedef unsigned long long int ULL;
 
#define PB push_back
#define MP make_pair
#define F first
#define S second
#define SZ(a) (int)(a.size())
#define ALL(a) a.begin(),a.end()
#define SET(a,b) memset(a,b,sizeof(a))
#define LET(x,a) __typeof(a) x(a)
 
#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))
//Works for forward as well as backward iteration
 
#define gu getchar
#define pu putchar
#define si(n) scanf("%d",&n)
#define dout(n) printf("%d\n",n)
#define sll(n) scanf("%lld",&n)
#define lldout(n) printf("%lld\n",n)
 
#define DRT() int t; si(t); while(t--)
 
#define PlUSWRAP(index,n) index = (index+1)%n		//index++; if(index>=n) index=0
#define MINUSWRAP(index,n) index = (index + n -1)%n 	//index--; if(index<0) index=n-1
#define ROUNDOFFINT(d) d = (int)((double)d + 0.5)	//Round off d to nearest integer
 
#define FLUSHN while(gu()!='\n')
#define FLUSHS while(gu()!=' ')
 
#define TRACE
 
#ifdef TRACE
#define trace1(x)                cerr << #x << ": " << x << endl;
#define trace2(x, y)             cerr << #x << ": " << x << " | " << #y << ": " << y << endl;
#define trace3(x, y, z)          cerr << #x << ": " << x << " | " << #y << ": " << y << " | " << #z << ": " << z << endl;
#define trace4(a, b, c, d)       cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << endl;
#define trace5(a, b, c, d, e)    cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << " | " << #e << ": " << e << endl;
#define trace6(a, b, c, d, e, f) cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << " | " << #e << ": " << e << " | " << #f << ": " << f << endl;
 
#else
 
#define trace1(x)
#define trace2(x, y)
#define trace3(x, y, z)
#define trace4(a, b, c, d)
#define trace5(a, b, c, d, e)
#define trace6(a, b, c, d, e, f)
 
#endif
 
//FILE *fin = freopen("in","r",stdin);
//FILE *fout = freopen("out","w",stdout);
const int N = int(5e4)+10;
const int LOGN = 17;
set<int> g[N];
int ndist[LOGN][N],sub[N];
int P[N],Pr[N],len;
LL ans;int nn;
 
void dfs1(int u,int p)
{
	sub[u]=1;nn++;
	for(auto it=g[u].begin();it!=g[u].end();it++)
		if(*it!=p)
			dfs1(*it,u),sub[u]+=sub[*it];
}
int dfs2(int u,int p)
{
	for(auto it=g[u].begin();it!=g[u].end();it++)
		if(*it!=p && sub[*it]>nn/2)
			return dfs2(*it,u);
	return u;
}
void dfs3(int u,int p,int depth,int dist,int add)
{
	ndist[depth][dist] += add;
	for(auto it=g[u].begin();it!=g[u].end();it++)
		if(*it!=p)
			dfs3(*it,u,depth,dist+1,add);
}
LL dfs4(int u,int p,int depth,int dist)
{
	LL ret = 0;
	for(int i=0;i<len;i++)
	{
		if(P[i]-dist<0)continue;
		if(!ndist[depth][P[i]-dist])break;
		if(P[i]!=dist)
			ret+=ndist[depth][P[i]-dist];
		else
			ret+=2*ndist[depth][P[i]-dist];
	}
	for(auto it=g[u].begin();it!=g[u].end();it++)
		if(*it!=p)
			ret+=dfs4(*it,u,depth,dist+1);
	return ret;
}
void decompose(int root,int depth)
{
	nn=0;
	dfs1(root,root);
	int centroid = dfs2(root,root);
	dfs3(centroid,centroid,depth,0,1);
	LL add=0;
	int u=centroid;
	for(auto it=g[u].begin();it!=g[u].end();it++)
	{
		dfs3(*it,u,depth,1,-1);
		add +=  dfs4(*it,u,depth,1);
		dfs3(*it,u,depth,1,1);
	}
	ans += add/2;
	for(auto it=g[u].begin();it!=g[u].end();it++)
	{
		g[*it].erase(u);
		decompose(*it,depth+1);
	}
	for(int i=0;i<N && ndist[depth][i];i++)
		ndist[depth][i]=0;
}
void genPrime()
{
	for(int i=2;i*i<N;i++)
		if(!Pr[i])
			for(int j = i*i;j<N;j+=i)
				Pr[j]=1;
	for(int i=2;i<N;i++)
		if(!Pr[i])
			P[len++]=i;
}
int main()
{
	genPrime();
	int n;
	si(n);
	for(int i=0;i<n-1;i++)
	{
		int a,b;
		scanf("%d %d",&a,&b);
		g[a-1].insert(b-1);
		g[b-1].insert(a-1);
	}
	decompose(0,0);
	double den = (LL)n*(LL)(n-1)/2.0;
	printf("%0.10lf\n",ans/den);
	return 0;
}
 