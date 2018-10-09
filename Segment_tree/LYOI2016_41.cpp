#include <bits/stdc++.h>
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
#define up rt,rt<<1,rt<<1|1
using namespace std;
const int M = 2e5+7;
typedef long long ll;
const ll mod = 1e9+7;
int n,q;
ll a[M],c[M];
char s[2];
int ql,qr,qpos,tot;ll qx,qk,qb;
struct Seg
{
	ll k[M<<3],b[M<<3];
	void pushup(int rt,int l,int r){
		k[rt]=k[l]*k[r]%mod;
		b[rt]=(b[l]*k[r]%mod+b[r])%mod;
	}
	void build(int l,int r,int rt){
		if(l==r){
			k[rt]=a[l],b[rt]=c[l];
			return ;
		}
		int mid=(l+r)>>1;
		build(lson);
		build(rson);
		pushup(up);
	}
	void update(int pos,int l,int r,int rt,ll a,ll c){
		if(l==r){
			k[rt]=a,b[rt]=c;
			return ;
		}
		int mid=(l+r)>>1;
		if(pos<=mid) update(pos,lson,a,c);
		else update(pos,rson,a,c);
		pushup(up);
	}
	int query(int L,int R,int l,int r,int rt){
		if(L<=l&&r<=R){
			return rt;
		}
		int mid=(l+r)>>1,ll,rr,res;
		if(L>mid){
			res=query(L,R,rson);
			return res;
		}
		else if(R<=mid){
			res=query(L,R,lson);
			return res;
		}
		else{
			ll=query(L,R,lson),rr=query(L,R,rson);
			pushup(++tot,ll,rr);
			return tot;
		}
	}
}seg;
void solve(){
	while(q--){
		scanf("%s",s);
		if(s[0]=='Q'){
			tot=(M<<2)+1;
			scanf("%d%d%lld",&ql,&qr,&qx);
			tot=seg.query(ql,qr,1,n,1);
			printf("%lld\n",(seg.k[tot]*qx%mod+seg.b[tot])%mod);
		}
		else{
			scanf("%d%lld%lld",&qpos,&qk,&qb);
			seg.update(qpos,1,n,1,qk,qb);
		}
	}
}
int main(){
	// freopen("1.in","r",stdin);
	// freopen("1.out","w",stdout);
	while(~scanf("%d%d",&n,&q)){
		for(int i=1;i<=n;i++) scanf("%lld%lld",&a[i],&c[i]);
		seg.build(1,n,1);
		solve();
	}
	return 0;
}