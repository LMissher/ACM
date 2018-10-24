#include <bits/stdc++.h>
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
#define up rt,rt<<1,rt<<1|1
using namespace std;
typedef long long ll;
const int Nmax = 1e4+7;
int n,q;ll a[Nmax];
struct Seg{
	ll sum[Nmax<<2],fsum[Nmax<<2],len[Nmax<<2],lazyadd[Nmax<<2],lazymul[Nmax<<2];
	void pushup(int rt,int l,int r){
		sum[rt]=sum[l]+sum[r];
		fsum[rt]=fsum[l]+fsum[r];
	}
	void pushdown(int rt,int l,int r){
		if(lazymul[rt]!=1){
			ll v=lazymul[rt];
			lazymul[rt]=1;
			sum[l]*=v;sum[r]*=v;
			fsum[l]*=(v*v);fsum[r]*=(v*v);
			lazymul[l]*=v;lazymul[r]*=v;
			lazyadd[l]*=v;lazyadd[r]*=v;
		}
		if(lazyadd[rt]){
			ll v=lazyadd[rt];
			lazyadd[rt]=0;
			fsum[r]+=(2*sum[r]*v+v*v*len[r]);fsum[l]+=(2*sum[l]*v+v*v*len[l]);
			sum[r]+=(v*len[r]);sum[l]+=(v*len[l]);
			lazyadd[r]+=v;lazyadd[l]+=v;
		}
	}
	void build(int l,int r,int rt){
		sum[rt]=fsum[rt]=0;len[rt]=(ll)(r-l+1);lazyadd[rt]=0;lazymul[rt]=1;
		if(l==r){
			sum[rt]=a[l];fsum[rt]=a[l]*a[l];
			return ;
		}
		int mid=(l+r)>>1;
		build(lson);
		build(rson);
		pushup(up);
	}
	void update(int L,int R,int l,int r,int rt,ll v,int op){
		if(L<=l&&r<=R){
			if(op==2){
				fsum[rt]+=(2*sum[rt]*v+v*v*len[rt]);
				sum[rt]+=(len[rt]*v);
				lazyadd[rt]+=v;
			}
			else{
				sum[rt]*=v;fsum[rt]*=(v*v);
				lazyadd[rt]*=v;lazymul[rt]*=v;
			}
			return ;
		}
		pushdown(up);
		int mid=(l+r)>>1;
		if(L<=mid) update(L,R,lson,v,op);
		if(R>mid) update(L,R,rson,v,op);
		pushup(up);
	}
	ll query(int L,int R,int l,int r,int rt,int op){
		if(L<=l&&r<=R){
			if(op==1) return sum[rt];
			else return fsum[rt];
		}
		pushdown(up);
		int mid=(l+r)>>1;ll res=0;
		if(L<=mid) res+=query(L,R,lson,op);
		if(R>mid) res+=query(L,R,rson,op);
		return res;
	}
}seg;
void solve(){
	while(q--){
		int op,l,r;ll v;
		scanf("%d",&op);
		if(op==1||op==2){
			scanf("%d%d",&l,&r);
			printf("%lld\n",seg.query(l,r,1,n,1,op));
		}
		else{
			scanf("%d%d%lld",&l,&r,&v);
			seg.update(l,r,1,n,1,v,op-2);
		}
	}
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	seg.build(1,n,1);
	solve();
	return 0;
}
