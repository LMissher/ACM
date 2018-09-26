#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9+7ll; 
int _;
ll n;
struct mat
{
	ll a[7][7];
	mat(){
		memset(a,0,sizeof(a));
	}
	void init(){
		for(int i=0;i<6;i++) a[i][i]=1;
	}
	mat operator * (const mat& t)const{
		mat tmp;
		for(int i=0;i<6;i++)
			for(int j=0;j<6;j++)
				for(int k=0;k<6;k++)
					tmp.a[i][j]=(tmp.a[i][j]+a[i][k]*t.a[k][j]%mod)%mod;
		return tmp;
	}
};
mat matrix_pow(mat x,ll k){
	mat ans,res;res=x;
	ans.init();
	while(k){
		if(k&1) ans=ans*res;
		res=res*res;
		k>>=1;
	}
	return ans;
}
int main(){
	mat x;
	x.a[0][0]=x.a[0][1]=x.a[0][2]=1ll;x.a[0][3]=x.a[0][5]=4ll;x.a[0][4]=6ll;
	x.a[1][0]=1ll;
	x.a[2][2]=x.a[2][5]=1ll;x.a[2][3]=x.a[2][4]=3ll;
	x.a[3][3]=x.a[3][5]=1ll;x.a[3][4]=2ll;
	x.a[4][4]=x.a[4][5]=1ll;
	x.a[5][5]=1ll;
	scanf("%d",&_);
	while(_--){
		scanf("%lld",&n);
		mat y=matrix_pow(x,n-1ll);
		printf("%lld\n",((((y.a[0][0]+y.a[0][2])%mod+y.a[0][3])%mod+y.a[0][4])%mod+y.a[0][5])%mod);
	}
	return 0;
}