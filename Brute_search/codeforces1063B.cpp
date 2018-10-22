#include <bits/stdc++.h>
using namespace std;
int sx,sy,limx,limy,n,m;
char s[2007][2007];
int flag[2007][2007];
struct node{
	int x,y,lx,ly;
	node(){}
	node(int xx,int yy,int llx,int lly){
		x=xx;y=yy;lx=llx;ly=lly;
	}
}d[2007][2007];
int tot;
void bfs(){
	memset(flag,0,sizeof(flag));
	queue<node> q;
	q.push(node(sx,sy,limx,limy));

#ifdef DEBUG
	//cout<<sx<<" "<<sy<<endl;
#endif
	while(!q.empty()){
		int x=q.front().x,y=q.front().y,lx=q.front().lx,ly=q.front().ly;
		q.pop();
		if(flag[x][y]&&d[x][y].lx>=lx&&d[x][y].ly>=ly) continue;
		if(!flag[x][y]) tot++;
		d[x][y].lx=lx;d[x][y].ly=ly;
		flag[x][y]=1;
		#ifdef DEBUG
			cout<<x<<" "<<y<<" "<<lx<<" "<<ly<<" "<<s[x][y]<<endl;
		#endif
		if(x-1>=1&&s[x-1][y]!='*'){
			q.push(node(x-1,y,lx,ly));
		}
		if(x+1<=n&&s[x+1][y]!='*'){
			q.push(node(x+1,y,lx,ly));
		}
		if(y-1>=1&&s[x][y-1]!='*'&&lx>=1){
			q.push(node(x,y-1,lx-1,ly));
		}
		if(y+1<=m&&s[x][y+1]!='*'&&ly>=1){
			q.push(node(x,y+1,lx,ly-1));
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	scanf("%d%d",&sx,&sy);
	scanf("%d%d",&limx,&limy);
	for(int i=1;i<=n;i++) scanf("%s",s[i]+1);
#ifdef DEBUG
	//cout<<sx<<" "<<sy<<endl;
#endif
	bfs();
	printf("%d\n",tot);
	return 0;
}