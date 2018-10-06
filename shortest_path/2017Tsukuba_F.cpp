#include <bits/stdc++.h>
using namespace std;
const int M = 1e5+7;
typedef long long ll;
const ll inf = 1e18+7;
int n,m;
int from[M],to[M],ans[M];ll val[M];
struct Dijkstra
{
    int cnt,head[M],flag[M];
    struct edge{
        int v,next;ll w;
    }e[M];
    void init(){
        cnt=0;memset(head,-1,sizeof(head));
    }
    void add(int u,int v,ll w){
        e[++cnt].v=v;e[cnt].w=w;e[cnt].next=head[u];
        head[u]=cnt;
    }
    struct node
    {
        int id;ll dis;
        bool operator < (const node & k)const {
            return dis>k.dis;
        } 
    }d[M];
    void dijkstra(int s){
        priority_queue<node> q;
        for(int i=1;i<=n;i++) d[i].id=i,d[i].dis=inf,flag[i]=0;
        d[s].dis=0;q.push(d[s]);
        while(!q.empty()){
            int u=q.top().id;q.pop();
            if(flag[u]) continue;
            flag[u]=1;
            for(int i=head[u];~i;i=e[i].next){
                int v=e[i].v;ll w=e[i].w;
                if(d[v].dis>d[u].dis+w){
                    d[v].dis=d[u].dis+w;
                    q.push(d[v]);
                }
            }
        }
        return ;
    }
}dijk,dijk1;
struct Tarjan
{
    int cnt,tot;
    int head[M],vis[M],dfn[M],low[M];
    struct edge
    {
        int v,next,id;ll w;
    }e[M];
    void init(){
        cnt=tot=0;memset(head,-1,sizeof(head));
        memset(dfn,-1,sizeof(dfn));memset(low,-1,sizeof(low));
        memset(vis,0,sizeof(vis));
    }
    void add(int u,int v,ll w,int i){
        e[++cnt].v=v;e[cnt].w=w;e[cnt].next=head[u];e[cnt].id=i;
        head[u]=cnt;
    }
    void tarjan(int u,int fa){
        dfn[u]=low[u]=++tot;
        vis[u]=1;
        for(int i=head[u];~i;i=e[i].next){
            int v=e[i].v;
            if(!vis[v]){
                tarjan(v,u);
                low[u]=min(low[u],low[v]);
                if(dfn[u]<low[v]){
                    ans[e[i].id]=-1;
                }
            }
            else if(fa!=v) low[u]=min(low[u],dfn[v]);
        }
    }
}tar;
map<tuple<int,int,int>,int> mp;
int main(){
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    while(~scanf("%d%d",&n,&m)){
        memset(ans,0,sizeof(ans));mp.clear();
        dijk.init();dijk1.init();tar.init();
        for(int i=1;i<=m;i++){
            scanf("%d%d%lld",&from[i],&to[i],&val[i]);mp[make_tuple(from[i],to[i],val[i])]++;
            dijk.add(from[i],to[i],val[i]);dijk1.add(to[i],from[i],val[i]);
        }
        dijk.dijkstra(1);dijk1.dijkstra(2);//从1到2的各个点的最短距离,从2到1的各个点的最短距离
        for(int i=1;i<=m;i++){
            if(dijk.d[2].dis>dijk.d[to[i]].dis+dijk1.d[from[i]].dis+val[i]) ans[i]=1;//反向之后比最短距离还小最短路变短
            if(dijk.d[2].dis==dijk.d[from[i]].dis+dijk1.d[to[i]].dis+val[i]){
                tar.add(from[i],to[i],val[i],i);tar.add(to[i],from[i],val[i],i);
            }
        }
        tar.tarjan(1,0);
        for(int i=1;i<=m;i++){//一条边只有是所有最短路的无向图里的桥且反向之后距离比最短距离大才会让最短路变长
            if(ans[i]==1) printf("HAPPY\n");
            else if(ans[i]==-1&&dijk.d[2].dis<dijk.d[to[i]].dis+dijk1.d[from[i]].dis+val[i]&&mp[make_tuple(from[i],to[i],val[i])]==1) printf("SAD\n");
            else printf("SOSO\n");
        }
    }
    return 0;
}