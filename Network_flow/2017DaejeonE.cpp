#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000;
const int MAXM = 4000;
const int inf = 0x3f3f3f3f;
struct edge{
	int to,next,cap,flow;
}e[MAXM];
int n,m;
int tol;
int head[MAXN];
int gap[MAXN],dep[MAXN],pre[MAXN],cur[MAXN];
void init(){
	tol=0;memset(head,-1,sizeof(head));
}
void addedge(int u,int v,int w,int rw=0){
	e[tol].to=v;e[tol].cap=w;e[tol].next=head[u];
	e[tol].flow=0;head[u]=tol++;
	e[tol].to=u;e[tol].cap=rw;e[tol].next=head[v];
	e[tol].flow=0;head[v]=tol++;
}
int sap(int st,int ed,int N){
	memset(gap,0,sizeof(gap));
	memset(dep,0,sizeof(dep));
	memcpy(cur,head,sizeof(head));
	int u=st;
	pre[u]=-1;
	gap[0]=N;
	int ans=0;
	while(dep[st]<N){
		if(u==ed){
			int Min=inf;
			for(int i=pre[u];~i;i=pre[e[i^1].to]){
				if(Min>e[i].cap-e[i].flow) Min=e[i].cap-e[i].flow;
			}
			for(int i=pre[u];~i;i=pre[e[i^1].to]){
				e[i].flow+=Min;
				e[i^1].flow-=Min;
			}
			u=st;
			ans+=Min;
			continue;
		}
		bool flag=false;
		int v;
		for(int i=cur[u];~i;i=e[i].next){
			v=e[i].to;
			if(e[i].cap-e[i].flow&&dep[v]+1==dep[u]){
				flag=true;
				cur[u]=pre[v]=i;
				break;
			}
		}
		if(flag){
			u=v;
			continue;
		}
		int Min=N;
		for(int i=head[u];~i;i=e[i].next){
			if(e[i].cap-e[i].flow&&dep[e[i].to]<Min){
				Min=dep[e[i].to];
				cur[u]=i;
			}
		}
		gap[dep[u]]--;
		if(!gap[dep[u]]) return ans;
		dep[u]=Min+1;
		gap[dep[u]]++;
		if(u!=st) u=e[pre[u]^1].to;
	}
	return ans;
}
struct E{
	int u,v,w,fl;
	bool operator < (const E &k) const{
		return w<k.w;
	}
}ee[1000];
int tot=0;
void solve(){
	int ans=0;
	for(int i=1;i<=tot;i++){
		init();
		for(int j=1;j<i;j++){
			if(ee[j].w<ee[i].w){
				addedge(ee[j].u,ee[j].v,1);
				addedge(ee[j].v,ee[j].u,1);
			}
		}
		ans+=sap(ee[i].u,ee[i].v,n);
	}
	printf("%d\n",ans);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		ee[++tot].u=u;ee[tot].v=v;ee[tot].w=w;ee[tot].fl=0;
	}
	sort(ee+1,ee+tot+1);
	solve();
	return 0;
}
