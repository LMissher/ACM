#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int Nmax = 2e5+7;
const ll mod = 998244353;
int n,m;
char s[Nmax],s1[Nmax];
ll presum[Nmax];
ll quickpow(ll a,ll b){
	ll res=a,ans=1;
	while(b){
		if(b&1) ans=ans*res%mod;
		res=res*res%mod;
		b>>=1;
	}
	return ans;
}
int main(){
	scanf("%d%d",&n,&m);
	scanf("%s",s);
	scanf("%s",s1);
	int l=strlen(s);
	for(int i=l-1;i>=0;i--){
		presum[i]=presum[i+1];
		if(s[i]=='1') presum[i]=(presum[i]+quickpow(2,l-i-1))%mod;
	}
	int l1=strlen(s1),tot=l-1;ll ans=0;
	for(int i=l1-1;i>=0;i--){
		if(s1[i]=='1') ans=(ans+presum[tot])%mod;
		if(tot!=0) tot--;
	}
	printf("%lld\n",ans);
	return 0;
}
