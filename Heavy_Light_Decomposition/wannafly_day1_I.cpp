#include <bits/stdc++.h>
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
#define up rt,rt<<1,rt<<1|1
using namespace std;
const int M = 1e5+7;
const int inf = 2147483647;
int n,m,k;
int tot,cnt,head[M];
int sz[M],f[M],son[M],dep[M],rnk[M],top[M],id[M];
int lazy[M<<2],mx[M<<2],ans[M];
struct edge
{
    int v,nex;
}e[M<<1];
void init(){
    tot=cnt=0;memset(head,-1,sizeof(head));memset(ans,0,sizeof(ans));
}
void add(int u,int v){
    e[++cnt].v=v;e[cnt].nex=head[u];
    head[u]=cnt;
}
void dfs(int u,int fa,int d){
    sz[u]=1,f[u]=fa,son[u]=-1,dep[u]=d;
    for(int i=head[u];~i;i=e[i].nex){
        int v=e[i].v;
        if(v==fa) continue;
        dfs(v,u,d+1);
        sz[u]+=sz[v];
        if(son[u]==-1||sz[v]>sz[son[u]]) son[u]=v;
    }
    return ;
}
void dfs1(int u,int t){
    id[u]=++tot;
    rnk[tot]=u;
    top[u]=t;
    if(son[u]==-1) return ;
    dfs1(son[u],t);
    for(int i=head[u];~i;i=e[i].nex){
        int v=e[i].v;
        if(v==f[u]||v==son[u]) continue;
        dfs1(v,v);
    }
    return ;
}
void pushup(int rt,int l,int r){
    mx[rt]=max(mx[l],mx[r]);
}
void pushdown(int rt,int l,int r){
    if(lazy[rt]>0){
        int v=lazy[rt];
        lazy[rt]=0;
        mx[r]+=v;lazy[r]+=v;
        mx[l]+=v;lazy[l]+=v;
    }
    return ;
}
void build(int l,int r,int rt){
    mx[rt]=0;lazy[rt]=0;
    if(l==r) return ;
    int mid=(l+r)>>1;
    build(lson);
    build(rson);
}
void update(int L,int R,int l,int r,int rt,int v){
    if(L<=l&&r<=R){
        if(mx[rt]==k-1){
            if(l==r){
                mx[rt]=-inf,ans[rnk[l]]=v,lazy[rt]=0;
            }
            else{
                pushdown(up);
                int mid=(l+r)>>1;
                if(mx[rt<<1]>=0) update(L,R,lson,v);
                if(mx[rt<<1|1]>=0) update(L,R,rson,v);
                pushup(up);
            }
        }
        else mx[rt]++,lazy[rt]++;
        return ;
    }
    pushdown(up);
    int mid=(l+r)>>1;
    if(L<=mid&&mx[rt<<1]>=0) update(L,R,lson,v);
    if(R>mid&&mx[rt<<1|1]>=0) update(L,R,rson,v);
    pushup(up);
    return ;
}
void query(int x,int y,int v){
    int fx=top[x],fy=top[y];
    while(fx!=fy){
        if(dep[fx]>dep[fy]){
            update(id[fx],id[x],1,n,1,v);
            x=f[fx],fx=top[x];
        }
        else{
            update(id[fy],id[y],1,n,1,v);
            y=f[fy],fy=top[y];
        }
    }
    if(dep[x]>dep[y])
        update(id[y],id[x],1,n,1,v);
    else
        update(id[x],id[y],1,n,1,v);
}
int qu[M],qv[M],qc[M];
int main(){
    //freopen("1.in","r",stdin);
    //freopen("1.out","w",stdout);
    init();
    scanf("%d%d%d",&n,&m,&k);
    build(1,n,1);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    dfs(1,-1,1);
    dfs1(1,1);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&qu[i],&qv[i],&qc[i]);
    }
    for(int i=m;i>=1;i--){
        query(qu[i],qv[i],qc[i]);
    }
    for(int i=1;i<=n;i++) printf("%d%c",ans[i],i==n?'\n':' ');
    return 0;
}
