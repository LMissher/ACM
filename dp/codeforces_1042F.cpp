#include <bits/stdc++.h>
using namespace std;
const int M = 1e6+7;
int n,k;
int ans,cnt,head[M],deg[M];
struct edge
{
	int v,next;
}e[M<<1];
void init(){
	cnt=0;memset(head,-1,sizeof(head));
}
void add(int u,int v){
	e[++cnt].v=v;e[cnt].next=head[u];
	head[u]=cnt;
}
int dfs(int u,int fa){
	if(deg[u]==1) return 0;
	vector<int> vec;
	for(int i=head[u];~i;i=e[i].next){
		int v=e[i].v;
		if(v==fa) continue;
		vec.push_back(dfs(v,u)+1);
	}
	sort(vec.begin(),vec.end());
	while(vec.size()>=2){
		if(vec[vec.size()-1]+vec[vec.size()-2]>k) ans++,vec.pop_back();
		else break;
	}
	return vec[vec.size()-1];
}
int main(){
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	init();
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);add(v,u);deg[u]++,deg[v]++;
	}
	for(int i=1;i<=n;i++)
		if(deg[i]>1){
			dfs(i,-1);break;
		}
	printf("%d\n",++ans);
	return 0;
}