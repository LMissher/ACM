#include <bits/stdc++.h>
// #define LMissher
using namespace std;
typedef long long ll;
const int M = 1e3+7;
const ll mod = 998244353;
int n,kk;
ll cnt[M][M<<1][4];
int main(){
	#ifdef LMissher
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	#endif
	scanf("%d%d",&n,&kk);
	cnt[1][1][0]=cnt[1][2][1]=cnt[1][2][2]=cnt[1][1][3]=1;
	for(int i=2;i<=n;i++)
		for(int j=1;j<=(n<<1);j++)
			for(int k=0;k<4;k++)
				for(int l=0;l<4;l++){
					if(!cnt[i-1][j][k]) continue;
					int xo=__builtin_popcount(k^l);
					if((l==0||l==3)&&xo>0) xo--;
					cnt[i][j+xo][l]=(cnt[i][j+xo][l]+cnt[i-1][j][k])%mod;
				}
	ll ans=0;
	for(int i=0;i<4;i++)
		ans=(ans+cnt[n][kk][i])%mod;
	printf("%lld\n",ans);
	return 0;
}