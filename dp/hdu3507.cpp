/*
斜率优化dp 形如 dp[i] = min( dp[j] + (val[i] - val[j])^2 + c )

这道题问给n个数，要你用最小的代价把n个数分成一些区间，代价是区间数和的平方加M的和。
得到递推式 dp[i] = min( dp[j] + (sum[i] - sum[j])^2 + M )
假设选择的点j优于k，那么 dp[j] + (sum[i] - sum[j])^2 + M < dp[k] + (sum[i] - sum[k])^2 + M
化简得到 (dp[j] + sum[j]^2 -dp[k] -sum[k]^2 ) / 2*( sum[j] - sum[k] ) < sum[i]
令 F[x] = dp[x] + sum[x]^2，则上式为 (F[j]-F[k])/2*(sum[j]-sum[k])<sum[i]
类似于一个斜率的式子，所以得到结果点对(i,j)满足上式则 i 更优于 j
且sum[i]是前缀和单调递增所以两点只要满足则之后也一定满足
到一个点时找到当前最优的点更新结果即可
如果先后三个点k，j，i，且(i,j)的式子结果小于(j,k)，那么j点必不可能是最优点，舍弃
用单调队列维护一个下凸的点集
*/
#include <bits/stdc++.h>
using namespace std;
const int M = 5e5+7;
int n,m;
int sum[M];
int dp[M];
int que[M],tail,head;
int getup(int i,int j){
	return dp[i]-dp[j]+sum[i]*sum[i]-sum[j]*sum[j]; 
}
int getdown(int i,int j){
	return 2*(sum[i]-sum[j]);
}
int getans(int i,int j){
	return dp[j]+(sum[i]-sum[j])*(sum[i]-sum[j])+m;
}
int main(){
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	while(~scanf("%d%d",&n,&m)){
		dp[0]=sum[0]=0;
		for(int i=1;i<=n;i++)
			scanf("%d",&sum[i]),sum[i]+=sum[i-1];
		que[0]=0;head=0,tail=1;
		for(int i=1;i<=n;i++){
			for(;head+1<tail && getup(que[head+1],que[head]) <= getdown(que[head+1],que[head])*sum[i];head++);
			dp[i]=getans(i,que[head]);
			for(;head+1<tail && getup(i,que[tail-1])*getdown(que[tail-1],que[tail-2]) <= getup(que[tail-1],que[tail-2])*getdown(i,que[tail-1]);tail--);
			que[tail++]=i;
		}
		printf("%d\n",dp[n]);
	}
	return 0;
}