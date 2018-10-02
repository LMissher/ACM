#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M = 1e5+7;
int n,k;ll x[M],q[M];
struct node
{
	ll x,r,q;
	int lp;
	bool operator < (const node & k) const {
		return x<k.x;
	}
}p[M];
struct Seg
{
	int tot;
	int T[M],L[M*40],R[M*40];ll sum[M*40];
	void update(int pos,int l,int r,int &rt,ll v){
		if(!rt) rt=++tot;
		sum[rt]+=v;
		if(l==r) return ;
		int mid=(l+r)>>1;
		if(pos<=mid) update(pos,l,mid,L[rt],v);
		else update(pos,mid+1,r,R[rt],v);
	}
	ll query(int l,int r,int Ll,int Rr,int rt){
		if(!rt) return 0;
		if(Ll<=l&&r<=Rr){
			return sum[rt];
		}
		int mid=(l+r)>>1;ll res=0;
		if(Ll<=mid) res+=query(l,mid,Ll,Rr,L[rt]);
		if(Rr>mid) res+=query(mid+1,r,Ll,Rr,R[rt]);
		return res;
	}
}seg;
vector<int> del[M];
int main(){
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld%lld",&p[i].x,&p[i].r,&p[i].q);x[i]=p[i].x;q[i]=p[i].q;
	}
	sort(p+1,p+n+1);sort(x+1,x+n+1);sort(q+1,q+n+1);
	int sz=unique(q+1,q+n+1)-q-1;
	for(int i=1;i<=n;i++){
		p[i].lp=lower_bound(x+1,x+n+1,p[i].x-p[i].r)-x;//左端覆盖位置
		del[upper_bound(x+1,x+n+1,p[i].x+p[i].r)-x].push_back(i);//右端覆盖位置
	}
	ll res=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<del[i].size();j++){
			seg.update(del[i][j],1,n,seg.T[lower_bound(q+1,q+sz+1,p[del[i][j]].q)-q],-1);//将只能覆盖到i-1的点移出
		}
		if(p[i].lp<i){
			for(int j=p[i].q-k;j<=p[i].q+k;j++){
				if(binary_search(q+1,q+sz+1,j)){
					res+=seg.query(1,n,p[i].lp,i-1,seg.T[lower_bound(q+1,q+sz+1,j)-q]);
				}
			}
		}
		seg.update(i,1,n,seg.T[lower_bound(q+1,q+sz+1,p[i].q)-q],1);//将新的点加入
	}
	printf("%lld\n",res);
	return 0;
}