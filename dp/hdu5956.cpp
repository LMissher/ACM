#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M = 1e5+7;
int _,n;
ll p,ans,len[M];
ll dp[M];
int cnt,frog[M];
int que[M],tail,head;
struct edge
{
	int v,nex;ll w;
}e[M<<1];
void init(){
	ans=p;head=tail=cnt=0;memset(frog,-1,sizeof(frog));
}
void add(int u,int v,ll w){
	e[++cnt].v=v;e[cnt].w=w;e[cnt].nex=frog[u];
	frog[u]=cnt;
}
void getlen(int u,int fa){
	for(int i=frog[u];~i;i=e[i].nex){
		int v=e[i].v;ll w=e[i].w;
		if(v==fa) continue;
		len[v]=len[u]+w;
		getlen(v,u);
	}
}
ll getup(int j,int k){
	return dp[j]-dp[k]+len[j]*len[j]-len[k]*len[k];
}
ll getdown(int j,int k){
	return 2ll*(len[j]-len[k]);
}
ll getans(int i,int j){
	return dp[j]+(len[i]-len[j])*(len[i]-len[j])+p;
}
void dfs(int u,int fa){
	int save_head=head;
	for(int i=frog[u];~i;i=e[i].nex){
		int v=e[i].v;
		if(v==fa) continue;
		while(head+1<tail && getup(que[head+1],que[head]) <= getdown(que[head+1],que[head])*len[v]) head++;
		dp[v]=getans(v,que[head]);
		ans=max(ans,dp[v]);
		vector<int> vec;
		while(head+1<tail && getup(v,que[tail-1])*getdown(que[tail-1],que[tail-2]) <= getup(que[tail-1],que[tail-2])*getdown(v,que[tail-1])){
			--tail;
			vec.push_back(que[tail]);
		}
		que[tail++]=v;
		dfs(v,u);
		--tail;
		for(int j=vec.size()-1;j>=0;j--){
			que[tail++]=vec[j];
		}
		head=save_head;	
	}
}
int main(){
	/*freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);*/
	scanf("%d",&_);
	while(_--){
		scanf("%d%lld",&n,&p);
		init();
		for(int i=1;i<n;i++){
			int u,v;ll w;
			scanf("%d%d%lld",&u,&v,&w);
			add(u,v,w);add(v,u,w);
		}
		getlen(1,-1);
		dp[1]=0ll;que[tail++]=1;
		dfs(1,-1);
		printf("%lld\n",ans-p);
	}
	return 0;
}