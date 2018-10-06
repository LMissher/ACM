#include <bits/stdc++.h>
using namespace std;
const int M = 2e5+7;
typedef long long ll;
const ll inf = 1e18+7;
int n,m,p;
int cnt,head[M],met[M],flag[M];
ll ans[M];
struct edge
{
	int v,next;ll w;
}e[M<<1];
void init(){
	cnt=0;memset(head,-1,sizeof(head));
}
void add(int u,int v,ll w){
	e[++cnt].v=v;e[cnt].w=w;e[cnt].next=head[u];
	head[u]=cnt;
}
struct node
{
	int id,act;ll dis;
	bool operator < (const node & k) const{
		return dis>k.dis;
	}
}d[M];
void dijkstra(){
	priority_queue<node> q;
	for(int i=1;i<=n;i++) d[i].id=i,d[i].act=0,d[i].dis=inf,flag[i]=0,ans[i]=inf;
	for(int i=1;i<=p;i++){
		d[met[i]].dis=0;d[met[i]].act=met[i];q.push(d[met[i]]);
	}
	while(!q.empty()){
		int u=q.top().id;
		q.pop();
		if(flag[u]) continue;
		flag[u]=1;
		for(int i=head[u];~i;i=e[i].next){
			int v=e[i].v;ll w=e[i].w;
			if(d[v].act&&d[v].act!=d[u].act){//某点的上一次更新来源和这次不同，更新这两个来源的答案
				ans[d[u].act]=min(ans[d[u].act],d[u].dis+d[v].dis+w);
				ans[d[v].act]=min(ans[d[v].act],d[u].dis+d[v].dis+w);
			}
			if(d[v].dis>d[u].dis+w){//更新某个点的最短距离及答案
				d[v].dis=d[u].dis+w;
				d[v].act=d[u].act;
				q.push(d[v]);
			}
		}
	}
	return ;
}
int main(){
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	init();
	scanf("%d%d%d",&n,&m,&p);
	for(int i=1;i<=p;i++) scanf("%d",&met[i]);
	for(int i=1;i<=m;i++){
		int u,v;ll w;
		scanf("%d%d%lld",&u,&v,&w);
		add(u,v,w);add(v,u,w);
	}
	dijkstra();
	for(int i=1;i<=p;i++) printf("%lld%c",ans[met[i]],i==p?'\n':' ');
	return 0;
}