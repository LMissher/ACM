#include <bits/stdc++.h>
using namespace std;
const int M = 1e5+7;
int n,m,k;
int a[M];
int que[M],que1[M],head,tail,head1,tail1;
int last;
int main(){
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	while(~scanf("%d%d%d",&n,&m,&k)){
		int ans=0;
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		last=0;
		head1=tail1=head=tail=1;
		for(int i=1;i<=n;i++){
			for(;head<tail&&a[que[tail-1]]<a[i];tail--);
			for(;head1<tail1&&a[que1[tail1-1]]>a[i];tail1--);
			que[tail++]=i;que1[tail1++]=i;
			while(a[que[head]]-a[que1[head1]]>k){
				if(que[head]<que1[head1]){
					last=que[head];
					head++;
				}
				else{
					last=que1[head1];
					head1++;
				}
			}
			if(a[que[head]]-a[que1[head1]]>=m){
				ans=max(ans,i-last);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}