#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M = 2e5+7;
int n,sz;
ll t,c[M],sum[M],tmp[M];
void update(int x,ll y){
	for(;x<=sz;x+=x&(-x)) c[x]+=y;
}
ll query(int x){
	ll res=0;
	for(;x>0;x-=x&(-x)) res+=c[x];
	return res;
}
int main(){
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	scanf("%d%lld",&n,&t);
	for(int i=1;i<=n;i++) scanf("%lld",&sum[i]),sum[i]+=sum[i-1],tmp[i]=sum[i];
	tmp[n+1]=0;sort(tmp+1,tmp+n+2);
	sz=unique(tmp+1,tmp+n+2)-tmp-1;update(lower_bound(tmp+1,tmp+sz+1,0)-tmp,1);
	ll ans=0;
	for(int i=1;i<=n;i++){
		int pos=lower_bound(tmp+1,tmp+sz+1,sum[i]-t)-tmp;
		ans+=query(sz)-(tmp[pos]==sum[i]-t?query(pos):query(pos-1));
		update(lower_bound(tmp+1,tmp+sz+1,sum[i])-tmp,1);
	}
	printf("%lld\n",ans);
	return 0;
}