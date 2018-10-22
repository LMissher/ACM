#include <bits/stdc++.h>
using namespace std;
const int Nmax = 1e5+7;
int tot,cnt,head[Nmax];
int n,match[Nmax],ans,fa[Nmax];
struct edge{
	int v,next;
}e[Nmax<<1];
void init(){
	tot=ans=cnt=0;memset(head,-1,sizeof(head));
}
void add(int u,int v){
	e[++cnt].v=v;e[cnt].next=head[u];
	head[u]=cnt;
}
vector<int> vec,nomat,use;
void dfs(int u){
	
#ifdef DEBUG
	cout<<u<<endl;
#endif
	for(int i=head[u];~i;i=e[i].next){
		int v=e[i].v;
		dfs(v);
		if(!match[u]&&!match[v]){
			ans++;
			match[u]=match[v]=1;
		}
		if(!match[v]) nomat.push_back(v);
	}
}
struct node{
	int rt,sz;
	vector<int> nomat;
	bool operator < (const node & k) const{
		return sz>k.sz;
	}
}nm[Nmax];
void solve(){
	sort(nm+1,nm+tot+1);
	for(int i=1;i<=tot;i++){
		int rt=nm[i].rt;
		if(!use.empty()){
			fa[rt]=use[use.size()-1];
			use.pop_back();
			ans++;
		}
		else{
			fa[rt]=1;
			use.push_back(rt);
		}
		for(int j=0;j<nm[i].nomat.size();j++){
			use.push_back(nm[i].nomat[j]);
		}
	}
	printf("%d\n",ans);
	for(int i=2;i<=n;i++) printf("%d%c",fa[i],i==n?'\n':' ');
}
int main(){
	init();
	scanf("%d",&n);
	vec.push_back(1);
	for(int i=2;i<=n;i++){
		int u;scanf("%d",&u);
		if(u!=0){
			add(u,i);
			fa[i]=u;
		}
		else vec.push_back(i);
	}
	for(int i=0;i<vec.size();i++){
		nomat.clear();
		dfs(vec[i]);
		if(match[vec[i]]||vec[i]==1){
			fa[vec[i]]=1;
			for(int j=0;j<nomat.size();j++){
				use.push_back(nomat[j]);
			}
			if(vec[i]==1&&!match[1]){
				use.push_back(1);
			}
		}
		else{
			nm[++tot].rt=vec[i];
			nm[tot].sz=nomat.size();
			nm[tot].nomat=nomat;
		}

#ifdef DEBUG
		cout<<ans<<endl;
#endif
	}
	solve();
	return 0;
}
