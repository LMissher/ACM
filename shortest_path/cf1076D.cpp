#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int Nmax = 3e5+7;
const ll inf = 1e18;
int n,m,k;
int cnt,head[Nmax],nxt[Nmax];
vector<pair<int,int> > vec[Nmax];
struct edge{
	int v,next;
	ll w;
}e[Nmax<<1];
void init(){
	cnt=0;memset(head,-1,sizeof(head));
	memset(nxt,-1,sizeof(nxt));
}
void add(int u,int v,ll w){
	e[++cnt].v=v;e[cnt].w=w;e[cnt].next=head[u];
	head[u]=cnt;
}
int flag[Nmax];
struct node{
	int index,e,p;ll dis;
	bool operator < (const node &k)const{
		return dis>k.dis;
	}
}d[Nmax];
void dijkstra(){
	for(int i=1;i<=n;i++) flag[i]=0,d[i].dis=inf,d[i].index=i;
	d[1].dis=0;priority_queue<node> q;q.push(d[1]);
	while(!q.empty()){
		int u=q.top().index;node nn=q.top();q.pop();
		if(flag[u]) continue;
		flag[u]=1;
		if(u>1){
			vec[nn.p].push_back(make_pair(u,nn.e));
		}
		for(int i=head[u];~i;i=e[i].next){
			int v=e[i].v;ll w=e[i].w;
			if(d[v].dis>d[u].dis+w){
				d[v].dis=d[u].dis+w;
				d[v].p=u,d[v].e=i;
				q.push(d[v]);
			}
		}
	}
}
int ans=0;
vector<int> v;
void dfs(int u){
	for(int i=0;i<vec[u].size();i++){
		int ee=vec[u][i].second;
		v.push_back(ee);ans++;
		if(ans==k) return ;
		dfs(vec[u][i].first);
		if(ans==k) return ;
	}
}
void solve(){
	dfs(1);	
	printf("%d\n",ans);
	for(int i=0;i<v.size();i++) printf("%d%c",(v[i]-1)/2+1,i==v.size()-1?'\n':' ');
}
int main(){
	init();
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++){
		int u,v;ll w;
		scanf("%d%d%lld",&u,&v,&w);
		add(u,v,w);add(v,u,w);
	}
	if(k==0){
		printf("0\n");
		return 0;
	}
	dijkstra();
	solve();
	return 0;
}