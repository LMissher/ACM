#include <bits/stdc++.h>
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
#define up rt,rt<<1,rt<<1|1
using namespace std;
typedef long long ll;
const int M = 1e5+7;
struct node
{
	int b,f;ll d;
	node () {}
	node (int b1,int f1,ll d1){
		b=b1;f=f1;d=d1;
	}
	bool operator < (const node & k)const {
		if(b!=k.b) return b<k.b;
		return f<k.f;
	}
}p[M];
map<node,ll> mp;
int n,tot,f[M];
struct Seg
{
	ll mx[M<<2];
	void pushup(int rt,int l,int r){
		mx[rt]=max(mx[l],mx[r]);
	}
	void build(int l,int r,int rt){
		if(l==r){
			mx[rt]=0;
			return ;
		}
		int mid=(l+r)>>1;
		build(lson);
		build(rson);
		pushup(up);
	}
	void update(int pos,int l,int r,int rt,ll v){
		if(l==r){
			if(v>mx[rt]) mx[rt]=v;
			return;
		}
		int mid=(l+r)>>1;
		if(pos<=mid) update(pos,lson,v);
		else update(pos,rson,v);
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
vector<pair<int,ll> > vec;
int main(){
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	while(~scanf("%d",&n)){
		mp.clear();tot=0;vec.clear();
		for(int i=1;i<=n;i++){
			int x,y;ll z;
			scanf("%d%d%lld",&x,&y,&z);
			mp[node(x,y,0)]+=z;
		}
		for(map<node,ll>::iterator it=mp.begin();it!=mp.end();it++){
			p[++tot].b=it->first.b;p[tot].f=it->first.f;p[tot].d=it->second;
			f[tot]=p[tot].f;
		}
		sort(p+1,p+tot+1);int pre=0;
		sort(f+1,f+tot+1);
		int sz=unique(f+1,f+tot+1)-f-1;
		seg.build(0,sz,1);
		for(int i=1;i<=tot;i++){
			if(p[i].b!=pre){
				for(int i=0;i<vec.size();i++){
					seg.update(vec[i].first,0,sz,1,vec[i].second);
				}
				vec.clear();
				int pos=lower_bound(f+1,f+sz+1,p[i].f)-f;
				vec.push_back(make_pair(pos,p[i].d+seg.query(0,pos-1,0,sz,1)));
				pre=p[i].b;
			}
			else{
				int pos=lower_bound(f+1,f+sz+1,p[i].f)-f;
				vec.push_back(make_pair(pos,p[i].d+seg.query(0,pos-1,0,sz,1)));
			}
		}
		for(int i=0;i<vec.size();i++){
			seg.update(vec[i].first,1,sz,1,vec[i].second);
		}
		printf("%lld\n",seg.mx[1]);
	}
	return 0;
}