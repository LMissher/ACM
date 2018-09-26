#include <bits/stdc++.h>
//#define LMissher
using namespace std;
int _,n,m,s;
int ans,cnt,head[107];
int mp[107][107],tmp[107];
struct edge
{
    int v,nex;
}e[1007];
void init(){
    ans=cnt=0;memset(head,-1,sizeof(head));
    memset(mp,0,sizeof(mp));
}
void add(int u,int v){
    e[++cnt].v=v;e[cnt].nex=head[u];
    head[u]=cnt;
}
void dfs(int u){
    if(tmp[0]==s){
        ans++;return ;
    }
    if(n-u<s-tmp[0]) return ;
    for(int i=head[u];~i;i=e[i].nex){
        int v=e[i].v,flg=1;
        for(int j=1;j<=tmp[0];j++){
            if(!mp[v][tmp[j]]){
                flg=0;
                break;
            }
        }
        if(flg){
            tmp[0]++;
            tmp[tmp[0]]=v;
            dfs(v);
            tmp[0]--;
        }
    }
    return ;
}
int main(){
    #ifdef LMissher
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif
    scanf("%d",&_);
    while(_--){
        init();
        scanf("%d%d%d",&n,&m,&s);
        for(int i=1;i<=m;i++){
            int u,v;
            scanf("%d%d",&u,&v);
            if(u>v) swap(u,v);
            add(u,v);mp[u][v]=mp[v][u]=1;
        }
        for(int i=1;i<=n;i++){
            tmp[0]=1;tmp[1]=i;
            dfs(i);
        }
        printf("%d\n",ans);
    }
    return 0;
}