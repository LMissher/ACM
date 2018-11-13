#include <bits/stdc++.h>
using namespace std;
const int inf = 2147483647;
int n,m,cnt,head[107];
int col[107];
struct edge{
	int v,next;
}e[10007];
void init(){
	cnt=0;memset(head,-1,sizeof(head));
}
void add(int u,int v){
	e[++cnt].v=v;e[cnt].next=head[u];
	head[u]=cnt;
}
struct node{
	int index,dis;
	bool operator < (const node &k)const{
		return dis>k.dis;
	}
}d[2][107];
int flag[107];
void dijkstra(int s,int x){
	for(int i=1;i<=n;i++) flag[i]=0,d[x][i].index=i,d[x][i].dis=inf;
	priority_queue<node> q;d[x][s].dis=0;q.push(d[x][s]);
	while(!q.empty()){
		int u=q.top().index;q.pop();
		if(flag[u]) continue;
		flag[u]=1;

		for(int i=head[u];~i;i=e[i].next){
			int v=e[i].v;
			if(d[x][v].dis>d[x][u].dis+1){
				d[x][v].dis=d[x][u].dis+1;
				q.push(d[x][v]);
			}
		}
	}
}
vector<int> vec;
int main(){
	init();
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&col[i]);
		if(col[i]){
			vec.push_back(i);
		}
	}
	for(int i=1;i<n;i++){
		int from,to;
		scanf("%d%d",&from,&to);
		add(from,to);add(to,from);
	}
	if(m==1){
		printf("0\n");
		return 0;
	}
	int ans=1e9;
	for(int i=0;i<vec.size();i++){
		for(int j=i+1;j<vec.size();j++){
			int u=vec[i],v=vec[j],tmp=0;
			dijkstra(u,0);dijkstra(v,1);
			int D=d[1][u].dis;
			for(int k=0;k<vec.size();k++){
				int y=vec[k];
				if(d[0][y].dis<=D&&d[1][y].dis<=D){
					tmp++;
				}
			}
			if(tmp>=m) ans=min(ans,D);
		}
	}
	printf("%d\n",ans);
	return 0;
}
