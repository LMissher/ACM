#include <bits/stdc++.h>
using namespace std;
const int Nmax = 1e6+7;
int n,a[Nmax],nxt[Nmax];
void get_next(){
	nxt[1]=0;
	int k=0;
	for(int q=2;q<=n;q++){
		while(k>0&&a[k+1]!=a[q]){
			k=nxt[k];
		}
		if(a[k+1]==a[q]){
			k=k+1;
		}
		nxt[q]=k;
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n/2;i++) swap(a[i],a[n-i+1]);
	get_next();
	int ans=2e9,k,p;
	for(int i=1;i<=n;i++){
		int xhj=i-nxt[i],jk=n-i;
		if(xhj+jk<ans||(xhj+jk==ans&&xhj<p)){
			ans=xhj+jk;
			k=jk;p=xhj;
		}
	}
	printf("%d %d\n",k,p);
	return 0;
}
