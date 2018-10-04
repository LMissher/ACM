#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M = 1e5+7;
inline int read(){
    int x=0; bool f=0; char ch=getchar();
    while (ch<'0' || '9'<ch) f|=ch=='-', ch=getchar();
    while ('0'<=ch && ch<='9') x=x*10+ch-'0', ch=getchar();
    return f?-x:x;
}
int n,m,q;
int ans,cnt,head[M],f[M];
int fa[M][26],mx[M][26],dep[M];
struct edge
{
	int v,next,w;
}e[M<<1];
struct edge1
{
	int u,v,w;
	edge1(){}
	edge1 (int u1,int v1,int w1) {
		u=u1,v=v1;w=w1;
	}
	bool operator < (const edge1 & k)const{
		if(w!=k.w) return w<k.w;
		if(w==k.w&&u!=k.u) return u<k.u;
		return v<k.v;
	}
}e1[M<<2];
map<edge1,int> mp;
void init(){
	ans=cnt=0;memset(head,-1,sizeof(head));mp.clear();
	memset(dep,0,sizeof(dep));memset(fa,0,sizeof(fa));memset(mx,0,sizeof(mx));
	for(int i=1;i<=n;i++) f[i]=i;
}
void add(int u,int v,int w){
	e[++cnt].v=v;e[cnt].next=head[u];e[cnt].w=w;
	head[u]=cnt;
}
int find(int x){return x==f[x]?x:f[x]=find(f[x]);}
void dfs(int u,int depth){
	dep[u]=depth;
	int j=1;
	while ((1<<j)<depth){
		fa[u][j]=fa[fa[u][j-1]][j-1];
		mx[u][j]=max(mx[u][j-1],mx[fa[u][j-1]][j-1]);
		j++;
	}
	for (int i=head[u];~i;i=e[i].next)
		if (dep[e[i].v]==0){
			int v=e[i].v;
			fa[v][0]=u;mx[v][0]=e[i].w;
			dfs(v,depth+1);
		}
}
void up(int &u,int step,int &res){
	for (int i=0;i<=20;i++) 
		if (step&(1<<i)) {
			res=max(mx[u][i],res);
			u=fa[u][i];
		}
	return ;
}
int work(int u,int v){
	int res=0;
	if (dep[u]<dep[v]) up(v,dep[v]-dep[u],res);
	else up(u,dep[u]-dep[v],res);
	for (int i=20;i>=0;i--)
		if (fa[u][i]!=fa[v][i]){
			res=max(res,max(mx[u][i],mx[v][i]));
			u=fa[u][i];v=fa[v][i];
		}
	if (u!=v) res=max(res,max(mx[u][0],mx[v][0]));
	return res;
}
void solve(){
	dfs(1,1);
	q=read();//scanf("%d",&q);
	while(q--){
		int u,v;
		scanf("%d%d",&u,&v);
		if(!mp[edge1(u,v,0)]) printf("%d\n",ans);
		else{
			printf("%d\n",ans-work(u,v)+mp[edge1(u,v,0)]);
		}
	}
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	while(~scanf("%d%d",&n,&m)){
		init();
		for(int i=1;i<=m;i++) e1[i].u=read(),e1[i].v=read(),e1[i].w=read();//scanf("%d%d%d",&e1[i].u,&e1[i].v,&e1[i].w);
		sort(e1+1,e1+m+1);
		for(int i=1;i<=m;i++){
			int fx=find(e1[i].u),fy=find(e1[i].v);
			if(fx!=fy){
				add(e1[i].u,e1[i].v,e1[i].w);add(e1[i].v,e1[i].u,e1[i].w);
				f[fx]=fy;
				ans+=e1[i].w;
			}
			else{
				mp[edge1(e1[i].u,e1[i].v,0)]=e1[i].w;mp[edge1(e1[i].v,e1[i].u,0)]=e1[i].w;
			}
		}
		solve();
	}
	return 0;
}