#include <bits/stdc++.h>
using namespace std;
int d,s,flag[507][5007];
struct node{
	int len;
	int sum,mod;
	char s[1007];
	node(){
		memset(s,0,sizeof(s));
	}
};
int main(){
	scanf("%d%d",&d,&s);
	node now;
	now.len=-1;now.sum=0;now.mod=0;
	queue<node> q;q.push(now);
	while(!q.empty()){
		now=q.front();q.pop();
		for(int i=0;i<=9;i++){
			if(now.len==-1&&i==0) continue;
			node nex=now;
			nex.len=now.len+1;
			nex.sum=now.sum+i;
			nex.mod=(now.mod*10+i)%d;
			nex.s[nex.len]=i+'0';

#ifdef DEBUG
			printf("%s\n",nex.s);
#endif
			if(flag[nex.mod][nex.sum]||nex.sum>s) continue;
			flag[nex.mod][nex.sum]=1;
			if(nex.mod==0&&nex.sum==s){
				printf("%s\n",nex.s);
				return 0;
			}
			q.push(nex);
		}
	}
	printf("-1\n");
	return 0;
}
