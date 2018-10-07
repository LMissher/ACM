#include <bits/stdc++.h>
using namespace std;
const int M = 1e5+7;
int n,m;
set<int> g[M];int vis[M];
void init(){
	for(int i=1;i<=n;i++) g[i].clear();memset(vis,0,sizeof(vis));
}
void topo(){
	queue<int> q;
	for(int i=1;i<=n;i++)
		if(g[i].size()==1) q.push(i);
	while(!q.empty()){
		int u=q.front(),v=*g[u].begin();q.pop();
		g[v].erase(u);
		g[u].clear();
		if(g[v].size()==1) q.push(v);
	}
}
void deldeg(){
	for(int i=1;i<=n;i++){
		if(g[i].size()==2){
			set<int>::iterator it=g[i].begin();
			int u=*it++;int v=*it;
			if(g[u].size()==2&&g[u].find(v)==g[u].end()){
				g[i].clear();
				g[u].erase(i);g[v].erase(i);
				g[u].insert(v);g[v].insert(u);
			}
		}
	}
}
int dfs(int u,int t){
	if(u==t) return 1;
	vis[u]=1;int res=0;
	for(set<int>::iterator it=g[u].begin();it!=g[u].end();it++){
		int v=*it;
		if(!vis[v]) res+=dfs(v,t);
	}
	vis[u]=0;
	return res;
}
void solve(){
	int ans=0;
	for(int i=1;i<=n;i++){
		while(g[i].size()){
			int v=*g[i].begin();
			g[v].erase(i);g[i].erase(v);
			ans+=dfs(i,v);
		}
	}
	printf("%d\n",ans);
}
int main(){
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	while(~scanf("%d%d",&n,&m)){
		init();
		for(int i=1,u,v;i<=m;i++){
			scanf("%d%d",&u,&v);
			g[u].insert(v);
			g[v].insert(u);
		}
		topo();
		deldeg();
		solve();
	}
	return 0;
}