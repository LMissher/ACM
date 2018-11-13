#include <bits/stdc++.h>
using namespace std;
const int Nmax = 5e5+7;
int n,m,q,tot;
int f[Nmax],rnk[Nmax],ans[Nmax];
vector<pair<int,int> > vec;
struct edge{
	int u,v,w,q;
	bool operator < (const edge & k)const {
		if(w!=k.w) return w<k.w;
		return q<k.q;
	}
}e[Nmax],qr[Nmax];
void init(){
	for(int i=1;i<=n;i++) f[i]=i,rnk[i]=1;
}
int find(int x){
	while(x!=f[x]) x=find(f[x]);
	return x;
}
void join(int x,int y){
	if(rnk[x]<rnk[y]) f[x]=y,rnk[y]+=rnk[x],vec.push_back(make_pair(y,x));
	else f[y]=x,rnk[x]+=rnk[y],vec.push_back(make_pair(x,y));
}
void remove(){
	for(int i=0;i<vec.size();i++){
		int x=vec[i].first,y=vec[i].second;
		rnk[x]-=rnk[y];f[y]=y;
	}
	vec.clear();
}
void solve(){
	int j=1,i=1;
	while(i<=tot){
		int x=qr[i].w,qq=qr[i].q;
		while(e[j].w<x){
			int fx=find(e[j].u),fy=find(e[j].v);
			if(fx!=fy){
				if(rnk[fx]<rnk[fy]) f[fx]=fy,rnk[fy]+=rnk[fx];
				else f[fy]=fx,rnk[fx]+=rnk[fy];
			}
			++j;
		}
		while(qr[i].w==x&&qr[i].q==qq&&i<=tot){
			int fx=find(qr[i].u),fy=find(qr[i].v);
			if(fx==fy){
				ans[qq]=1;
				break;
			}
			else{
				join(fx,fy);
			}
			++i;
		}
		while(qr[i].w==x&&qr[i].q==qq&&i<=tot) ++i;
		remove();
	}
	for(int i=1;i<=q;i++) ans[i]==1?printf("NO\n"):printf("YES\n");
}
int main(){
	scanf("%d%d",&n,&m);
	init();
	for(int i=1;i<=m;i++){
		int from,to,val;
		scanf("%d%d%d",&from,&to,&val);
		e[i].u=from,e[i].v=to,e[i].w=val;
	}
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		int x;
		scanf("%d",&x);
		for(int j=1;j<=x;j++){
			int y;
			scanf("%d",&y);
			qr[++tot].u=e[y].u,qr[tot].v=e[y].v,qr[tot].w=e[y].w,qr[tot].q=i;
		}
	}
	sort(e+1,e+m+1);sort(qr+1,qr+tot+1);
	solve();
	return 0;
}
