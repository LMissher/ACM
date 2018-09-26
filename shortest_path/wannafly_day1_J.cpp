#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M = 1e5+7;
const ll inf = 1e18;
int n,m,q;
int sz,tmp,cnt,cnt1,head[M],pre[M],head1[M];
ll treedis[M];
struct edge
{
	int v,nex;ll w;
}e[M<<1],e1[M<<4];
void init(){
	tmp=cnt1=cnt=0;memset(head,-1,sizeof(head));memset(head1,-1,sizeof(head1));
	memset(treedis,0,sizeof(treedis));
	for(int i=1;i<=n;i++) pre[i]=i;
}
void add(int u,int v,ll w){
	e[++cnt].v=v;e[cnt].w=w;e[cnt].nex=head[u];
	head[u]=cnt;
}
void add1(int u,int v,ll w){
	e1[++cnt1].v=v;e1[cnt1].w=w;e1[cnt1].nex=head1[u];
	head1[u]=cnt1;
}
int find(int x){return x==pre[x]?x:pre[x]=find(pre[x]);}
int f[M][22],deep[M];
void dfs(int u,int fa,int d,ll len){//dfs(1,-1,0)
	treedis[u]=len;
    deep[u]=d;
    for(int i=head[u];~i;i=e[i].nex){
        int v=e[i].v;ll w=e[i].w;
        if(v==fa) continue;
        dfs(v,u,d+1,len+w);
        f[v][0]=u;
    }
    return ;
}
void work(){//RMQ
    for(int i=1;i<20;i++)
        for(int j=1;j<=n;j++) f[j][i]=f[f[j][i-1]][i-1];
}
int lca(int x,int y){//lca
    if(deep[x]<deep[y]) swap(x,y);
    int dt=deep[x]-deep[y];
    for(int i=0;i<20;i++) if(dt&(1<<i)) x=f[x][i];
    if(x==y) return x;
    for(int i=19;i>=0;i--) if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
    return f[x][0];
}
struct node
{
	int id;ll dis;
	bool operator < (const node & k)const {
		return dis>k.dis;
	}
}d[300][M];
int flag[M];
void dijkstra(int s,int index){
	for(int i=1;i<=n;i++) flag[i]=0,d[index][i].id=i,d[index][i].dis=inf;
	priority_queue<node> q;d[index][s].dis=0ll;q.push(d[index][s]);
	while(!q.empty()){
		int u=q.top().id;
		q.pop();
		if(flag[u]) continue;
		flag[u]=1;
		for(int i=head1[u];~i;i=e1[i].nex){
			int v=e1[i].v;ll w=e1[i].w;
			if(d[index][v].dis>d[index][u].dis+w){
				d[index][v].dis=d[index][u].dis+w;
				q.push(d[index][v]);
			}
		}
	}

	return ;
}
ll getdis(int u,int v){
	return treedis[u]+treedis[v]-2ll*treedis[lca(u,v)];
}
void solve(){
	int u,v;
	scanf("%d%d",&u,&v);
	ll dis=getdis(u,v);
	for(int i=1;i<=sz;i++){
		dis=min(dis,d[i][u].dis+d[i][v].dis);
	}
	printf("%lld\n",dis);
}
int mn[300];
int main(){
	scanf("%d%d",&n,&m);
	init();
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		if(find(u)!=find(v)){
			add(u,v,1ll);add(v,u,1ll);
			pre[find(u)]=find(v);
		}
		else if(find(u)==find(v)){
			mn[++tmp]=u;mn[++tmp]=v;
		}
		add1(u,v,1ll);add1(v,u,1ll);
	}
	dfs(1,-1,0,0ll);
	work();
	sort(mn+1,mn+1+tmp);
	sz=unique(mn+1,mn+1+tmp)-mn-1;
	for(int i=1;i<=sz;i++) dijkstra(mn[i],i);
	scanf("%d",&q);
	while(q--){
		solve();
	}
	return 0;
}