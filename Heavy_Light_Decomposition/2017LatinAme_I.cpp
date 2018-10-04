#include <bits/stdc++.h>
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
#define up rt,rt<<1,rt<<1|1
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
int tot,cnt,head[M],f[M];
ll ans;
struct edge
{
	int v,next;ll w;
}e[M<<1];
struct edge1
{
	int u,v;ll w;
	edge1(){}
	edge1 (int u1,int v1,ll w1) {
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
	tot=ans=cnt=0;memset(head,-1,sizeof(head));mp.clear();
	for(int i=1;i<=n;i++) f[i]=i;
}
void add(int u,int v,ll w){
	e[++cnt].v=v;e[cnt].next=head[u];e[cnt].w=w;
	head[u]=cnt;
}
int find(int x){return x==f[x]?x:f[x]=find(f[x]);}
int sz[M],dep[M],fat[M],son[M],rnk[M],id[M],top[M];ll val[M];
void dfs(int u,int fa,int d){
	sz[u]=1;dep[u]=d;son[u]=-1,fat[u]=fa;
	for(int i=head[u];~i;i=e[i].next){
		int v=e[i].v;ll w=e[i].w;
		if(v==fa) continue;
		val[v]=w;
		dfs(v,u,d+1);
		sz[u]+=v;
		if(son[u]==-1||sz[v]>sz[son[u]]) son[u]=v;
	}
	return ;
}
void dfs1(int u,int t){
	id[u]=++tot;
	rnk[tot]=u;
	top[u]=t;
	if(son[u]==-1) return;
	dfs1(son[u],t);
	for(int i=head[u];~i;i=e[i].next){
		int v=e[i].v;
		if(v==fat[u]||v==son[u]) continue;
		dfs1(v,v);
	}
	return ;
}
struct Seg
{
	ll mx[M<<2];
	void pushup(int rt,int l,int r){
		mx[rt]=max(mx[l],mx[r]);
	}
	void build(int l,int r,int rt){
		if(l==r){
			mx[rt]=val[rnk[l]];
			return ;
		}
		int mid=(l+r)>>1;
		build(lson);
		build(rson);
		pushup(up);
	}
	ll query(int L,int R,int l,int r,int rt){
		if(L<=l&&r<=R){
			return mx[rt];
		}
		int mid=(l+r)>>1;ll res=0;
		if(L<=mid) res=max(res,query(L,R,lson));
		if(R>mid) res=max(res,query(L,R,rson));
		return res;
	}
}seg;
ll query(int x,int y){
	int fx=top[x],fy=top[y];ll res=0;
	while(fx!=fy){
		if(dep[fx]>dep[fy]){
			res=max(res,seg.query(id[fx],id[x],1,n,1));
			x=fat[fx],fx=top[x];
		}
		else{
			res=max(res,seg.query(id[fy],id[y],1,n,1));
			y=fat[fy],fy=top[y];
		}
	}
	if(x==y) return res;
	if(dep[x]>dep[y])
		res=max(res,seg.query(id[son[y]],id[x],1,n,1));
	else
		res=max(res,seg.query(id[son[x]],id[y],1,n,1));
	return res;
}
void solve(){
	dfs(1,-1,0);dfs1(1,1);seg.build(1,n,1);
	q=read();//scanf("%d",&q);
	while(q--){
		int u,v;
		scanf("%d%d",&u,&v);
		if(!mp[edge1(u,v,0)]) printf("%lld\n",ans);
		else{
			printf("%lld\n",ans-query(u,v)+mp[edge1(u,v,0)]);
		}
	}
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	while(~scanf("%d%d",&n,&m)){
		init();
		for(int i=1;i<=m;i++) e1[i].u=read(),e1[i].v=read(),e1[i].w=read();//scanf("%d%d%lld",&e1[i].u,&e1[i].v,&e1[i].w);
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