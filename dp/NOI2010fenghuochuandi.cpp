#include <bits/stdc++.h>
using namespace std;
const int M = 1e6+7;
int n,m;
int a[M],dp[M];
int que[M],head,tail;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	tail=head=1;
	for(int i=1;i<=n;i++){
		for(;head<tail&&i-que[head]>m;head++);
		dp[i]=a[i]+dp[que[head]];
		for(;head<tail&&dp[que[tail]]>dp[i];tail--);
		que[++tail]=i;
	}
	int ans=2147483647;
	for(int i=n-m+1;i<=n;i++) ans=min(ans,dp[i]);
	printf("%d\n",ans);
	return 0;
}