#include <bits/stdc++.h>
using namespace std;
const int M = 1e5+7;
int n;
int cnt,head[M];
int sz[M],f[M],son[M],x[M],y[M],tmp[M];
struct edge
{
    int v,next;
}e[M<<1];
void init(){
    cnt=0;memset(head,-1,sizeof(head));memset(tmp,0,sizeof(tmp));
}
void add(int u,int v){
    e[++cnt].v=v;e[cnt].next=head[u];
    head[u]=cnt;
}
void dfs(int u,int fa){
    sz[u]=1,f[u]=fa,son[u]=-1;
    for(int i=head[u];~i;i=e[i].next){
        int v=e[i].v;
        if(v==fa) continue;
        dfs(v,u);
        sz[u]+=sz[v];
        if(son[u]==-1||sz[v]>sz[son[u]]) son[u]=v;
    }
    return ;
}
void dfs1(int u,int z){
    y[u]=z;x[u]=++tmp[z];
    if(son[u]==-1) return;
    for(int i=head[u];~i;i=e[i].next){
        int v=e[i].v;
        if(v==f[u]||v==son[u]) continue;
        dfs1(v,z+1);
    }
    dfs1(son[u],z);
    return ;
}
int main(){
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    while(~scanf("%d",&n)){
        init();
        for(int i=1;i<n;i++){
            int u,v;
            scanf("%d%d",&u,&v);
            add(u,v);add(v,u);
        }
        dfs(1,-1);dfs1(1,1);
        for(int i=1;i<=n;i++) printf("%d %d\n", x[i],y[i]);
    }
    return 0;
}