#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M = 1e5+7;
int _,n,k,cas=1;
int cnt,head[M],tot;
struct edge
{
	int v,nex;
}e[M<<1];
int son[M],f[M];
ll sz[M],a[M],tmp[M],ans[M];
void init(){
	tot=cnt=0;memset(head,-1,sizeof(head));
}
void add(int u,int v){
	e[++cnt].v=v;e[cnt].nex=head[u];
	head[u]=cnt;
}
void dfs(int u,int fa){
	sz[u]=a[u];son[u]=-1;f[u]=fa;
	for(int i=head[u];~i;i=e[i].nex){
		int v=e[i].v;
		if(v==fa) continue;
		dfs(v,u);
		if(sz[v]>sz[son[u]]||son[u]==-1){
			sz[u]=sz[u]-sz[son[u]]+sz[v];
			son[u]=v;
		}
	}
}
void dfs1(int u,ll w){
	tmp[u]=a[u]+w;
	if(son[u]==-1){
		ans[++tot]=tmp[u];
		return ;
	}
	dfs1(son[u],tmp[u]);
	for(int i=head[u];~i;i=e[i].nex){
		int v=e[i].v;
		if(v==f[u]||v==son[u]) continue;
		dfs1(v,0);
	}
	return ;
}
int main(){
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	scanf("%d",&_);
	while(_--){
		init();
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
		for(int i=1;i<n;i++){
			int u,v;
			scanf("%d%d",&u,&v);
			add(u,v);add(v,u);
		}
		dfs(1,-1);
		// for(int i=1;i<=n;i++) printf("%d %d\n",f[i],son[i]);
		dfs1(1,0);
		ll res=0;
		printf("Case #%d: ",cas++);
		if(k>tot){
			for(int i=1;i<=tot;i++) res+=ans[i];
			printf("%lld\n",res);
		}
		else{
			sort(ans+1,ans+1+tot);
			for(int i=tot;i>tot-k;i--) res+=ans[i];
			printf("%lld\n",res);
		}
	}
	return 0;
}