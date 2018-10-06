#include <bits/stdc++.h>
using namespace std;
const int maxn=2010,inf=0x3f3f3f3f;
int n,m,st[407],ed[407],st1[407],ed1[407],ans,ans1;
priority_queue<int,vector<int>,greater<int> > q;
vector<int> s[407],s1[407];
void init(){
	while(!q.empty()) q.pop();ans=0;ans1=0;
	for(int i=1;i<=401;i++) s[i].clear(),s1[i].clear();
}
struct Dinic
{
	struct edge
	{
	    int from,to,cap,flow;
	};
	vector<edge>es;
	vector<int>G[maxn];
	bool vis[maxn];
	int dist[maxn];
	int iter[maxn];
	void init(int n){
	    for(int i=0; i<=n+10; i++)
	        G[i].clear();
	    es.clear();
	}
	void addedge(int from,int to,int cap){
	    es.push_back((edge){
	        from,to,cap,0
	    });
	    es.push_back((edge){
	        to,from,0,0
	    });
	    int x=es.size();
	    G[from].push_back(x-2);
	    G[to].push_back(x-1);
	}
	bool BFS(int s,int t){
	    memset(vis,0,sizeof(vis));
	    queue <int> Q;
	    vis[s]=1;
	    dist[s]=0;
	    Q.push(s);
	    while(!Q.empty()){
	        int u=Q.front();
	        Q.pop();
	        for(int i=0; i<G[u].size(); i++){
	            edge &e=es[G[u][i]];
	            if(!vis[e.to]&&e.cap>e.flow)
	            {
	                vis[e.to]=1;
	                dist[e.to]=dist[u]+1;
	                Q.push(e.to);
	            }
	        }
	    }
	    return vis[t];
	}
	int DFS(int u,int t,int f){
	    if(u==t||f==0)
	        return f;
	    int flow=0,d;
	    for(int &i=iter[u]; i<G[u].size(); i++){
	        edge &e=es[G[u][i]];
	        if(dist[u]+1==dist[e.to]&&(d=DFS(e.to,t,min(f,e.cap-e.flow)))>0){
	            e.flow+=d;
	            es[G[u][i]^1].flow-=d;
	            flow+=d;
	            f-=d;
	            if(f==0)
	                break;
	        }
	    }
	    return flow;
	}
	int Maxflow(int s,int t){
	    int flow=0;
	    while(BFS(s,t))
	    {
	        memset(iter,0,sizeof(iter));
	        int d=0;
	        while(d=DFS(s,t,inf))
	            flow+=d;
	    }
	    return flow;
	}
}dinic;
int main(){
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	while(~scanf("%d%d",&n,&m)){
		init();dinic.init(1000+n);
		for(int i=1;i<=m;i++){
			scanf("%d%d",&st[i],&ed[i]);
			s[st[i]].push_back(ed[i]);
		}
		for(int i=1;i<=n-m;i++){
			scanf("%d%d",&st1[i],&ed1[i]);
			s1[st1[i]].push_back(ed1[i]);
		}
		for(int i=1;i<=400;i++){
			for(int j=0;j<s[i].size();j++) q.push(s[i][j]);
			for(int j=0;j<s1[i].size();j++) q.push(s1[i][j]);
			while(!q.empty()){
				if(q.top()<i) q.pop();
				else{
					q.pop();
					ans++;
					break;
				}
			}
		}
		printf("%d\n",ans);
		int s=0,t=800+n+1;
		for(int i=m+1;i<=m+400;i++){
			dinic.addedge(i,i+400,1);
		}
		for(int i=1;i<=m;i++){
			dinic.addedge(s,i,1);
			for(int j=st[i];j<=ed[i];j++) dinic.addedge(i,m+j,1);
		}
		for(int i=1;i<=n-m;i++){
			dinic.addedge(m+800+i,t,1);
			for(int j=st1[i];j<=ed1[i];j++) dinic.addedge(m+400+j,m+800+i,1);
		}
		printf("%d\n",dinic.Maxflow(s,t));
	}
	return 0;
}