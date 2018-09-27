/*
单调队列优化dp
形如 dp[i][j] = dp[r][k] + x*k + c 的式子皆可用单调队列优化

这道题问给 t 天，每天有能买入卖出股票的数量，以及买入卖出股票的价格，交易每隔 w + 1 天进行
这题很容易想到用 dp[i][j] ，第 i 天有 j 只股票赚的钱
转移方程为 dp[i][j] = max(dp[i-1][j], max( dp[r][k] - API[i] * ( j - k ) | (j>k) , dp[r][k] + BPI[i] * ( k - j )  | (k>j)) )
其中第一种情况是这一天什么都不做，第二种情况是找到1<=r<=i-w-1中有k只股票再买一些能达到j只股票，第三种是找到1<=r<=i-w-1中有k只股票再卖一些能达到j只股票
但显然这样的复杂度是t*p*p的
考虑dp[i][j]>=dp[i-1][j]恒成立，所有只用考虑 r = i-w-1 的情况即可。
化简式子得到 买入: (dp[i-w-1][k]+API[i]*k)-API[i]*j  卖出: (dp[i-w-1][k]+BPI[i]*k)-BPI[i]*j
所以只用找到最大的括号里的式子即可
枚举k与j，可以同时枚举，因为如果k>j则买入必不可能，卖出同理
单调队列维护之前的最大值即可
*/
#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9+7;
struct pro
{
	int p,val;
}que[2100],tmp;
int head,tail;
int _,t,maxp,w;
int api[2100],bpi[2100],asi[2100],bsi[2100];
int dp[2100][2100];//i day j stock
void init(){
	for(int i=1;i<=t;i++)
		for(int j=0;j<=maxp;j++) dp[i][j]=-inf;
	for(int i=1;i<=w+1;i++)
		for(int j=0;j<=asi[i];j++) dp[i][j]=-api[i]*j;//开始拥有j只股票
}
int main(){
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	scanf("%d",&_);
	while(_--){
		scanf("%d%d%d",&t,&maxp,&w);
		for(int i=1;i<=t;i++)
			scanf("%d%d%d%d",&api[i],&bpi[i],&asi[i],&bsi[i]);
		init();
		for(int i=2;i<=t;i++){
			for(int j=0;j<=maxp;j++){
				dp[i][j]=max(dp[i][j],dp[i-1][j]);
			}
			if(i<=w+1) continue;//无法买卖
			head=tail=1;
			for(int j=0;j<=maxp;j++){//买入
				tmp.p=j;tmp.val=dp[i-w-1][j]+api[i]*j;//之前那天有k只股票
				for(;head<tail&&que[tail-1].val<tmp.val;tail--);
				que[tail++]=tmp;
				for(;head<tail&&que[head].p+asi[i]<j;head++);//之前的股票加上今天能买的还不能达到j只股票
				dp[i][j]=max(dp[i][j],que[head].val-api[i]*j);
			}
			head=tail=1;
			for(int j=maxp;j>=0;j--){
				tmp.p=j;tmp.val=dp[i-w-1][j]+bpi[i]*j;
				for(;head<tail&&que[tail-1].val<tmp.val;tail--);
				que[tail++]=tmp;
				for(;head<tail&&que[head].p-bsi[i]>j;head++);
				dp[i][j]=max(dp[i][j],que[head].val-bpi[i]*j);
			}
		}
		int ans=-inf;
		for(int i=0;i<=maxp;i++) ans=max(ans,dp[t][i]);
		printf("%d\n",ans);
	}
	return 0;
}