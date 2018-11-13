#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
const int Nmax = 3e5+7;
int n,q;
int cnt,head[Nmax];
ll ans[Nmax],dep[Nmax];
vector<pair<int,ll> > vec[Nmax];
struct edge{
	int v,next;
}e[Nmax<<1];
void init(){
	cnt=0;memset(head,-1,sizeof(head));
	memset(dep,0,sizeof(dep));
}
void add(int u,int v){
	e[++cnt].v=v;e[cnt].next=head[u];
	head[u]=cnt;
}
void dfs(int u,int fa,int d,ll val){
	for(int i=0;i<vec[u].size();i++){
		val+=vec[u][i].se;
		dep[min(d+vec[u][i].fi,300002)]+=vec[u][i].se;
	}
	ans[u]=val;
	for(int i=head[u];~i;i=e[i].next){
		int v=e[i].v;
		if(v==fa) continue;
		dfs(v,u,d+1,val-dep[d]);
	}
	for(int i=0;i<vec[u].size();i++) dep[min(d+vec[u][i].fi,300002)]-=vec[u][i].se;
}
int main(){
	init();
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		int x,y;ll w;
		scanf("%d%d%lld",&x,&y,&w);
		vec[x].push_back(make_pair(y,w));
	}
	dfs(1,-1,1,0);
	for(int i=1;i<=n;i++) printf("%lld%c",ans[i],i==n?'\n':' ');
	return 0;
}
