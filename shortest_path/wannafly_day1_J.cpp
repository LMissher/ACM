#include<bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,unsafe-math-optimizations")
#pragma GCC target("avx")
#define fi first
#define se second
#ifdef CX_TEST
#define Debug printf
#else
#define Debug(...)
#endif
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
  
const int mod = 998244353;
const int maxn = 1e5 + 5;
  
const int BUFFER_MAX_SIZE = 100000;
struct Quick_In {
    char buf[BUFFER_MAX_SIZE], *ps = buf, *pe = buf + 1;
    inline void InNext() {
        if (++ps == pe)
            pe = (ps = buf) + fread(buf, sizeof(char), sizeof(buf) / sizeof(char), stdin);
    }
    template<class T>
    inline bool operator()(T &number) {
        number = 0;
        T f = 1;
        bool vis_point = 0;
        if (ps == pe) return false; //EOF
        do {
            InNext();
            if ('-' == *ps) f = -1;
        } while (ps != pe && !isdigit(*ps));
        if (ps == pe) return false; //EOF
        do {
            if((*ps) == '.') vis_point = 1;
            else {
                number = number * 10 + *ps - 48;
                if(vis_point) f *= 0.1;
            }
            InNext();
        } while (ps != pe && (isdigit(*ps) || (*ps) == '.'));
        number *= f;
        return true;
    }
} In;
struct Quick_Out {
    char buf[BUFFER_MAX_SIZE], *ps = buf, *pe = buf + BUFFER_MAX_SIZE;
    char tmp[100];
    inline void write() {
        fwrite(buf, sizeof(char), ps - buf, stdout);
        ps = buf;
    }
    inline void oc(char c) {
        *(ps++) = c;
        if (ps == pe) write();
    }
    inline void os(char *s) {
        for (int i = 0; s[i]; ++i) oc(s[i]);
    }
    template<class T>
    inline void oi(T x, char bc = '\n') {
        if (x < 0) oc('-'), x = -x;
        int len = 0;
        if (!x) tmp[len++] = '0';
        while (x) tmp[len++] = x % 10 + '0', x /= 10;
        while (len)  oc(tmp[--len]);
        oc(bc);
    }
    ~Quick_Out() {
        write();
    }
} Out;
  
vector<int> g[maxn], p;
int d[maxn], st[maxn][18];
int f[105][maxn], vis[maxn], Tt = 1;
bool cv[maxn];
  
void dfs(int u, int fa) {
    vis[u] = Tt;
    for(auto v : g[u]) {
        if(v == fa) continue;
        if(vis[v] == Tt) {
            if(cv[u] || cv[v]) continue;
            p.push_back(u);
            cv[u] = 1;
            continue;
        }
        d[v] = d[u] + 1;
        st[v][0] = u;
        for(int i = 1; i < 18; i++) st[v][i] = st[st[v][i - 1]][i - 1];
        dfs(v, u);
    }
}
  
int lca(int u, int v) {
    if(d[u] > d[v]) swap(u, v);
    int x = d[v] - d[u];
    for(int i = 0; i < 18; i++) {
        if((x >> i) & 1) v = st[v][i];
    }
    if(u != v) {
        for(int i = 17; i >= 0; i--) {
            if(st[u][i] != st[v][i]) {
                u = st[u][i];
                v = st[v][i];
            }
        }
        u = st[u][0];
    }
    return u;
}
  
int q[maxn];
void bfs(int k, int u) {
    int h, t;
    h = t = 0;
    q[t++] = u;
    vis[u] = ++Tt;
    while(h < t) {
        u = q[h++];
        for(auto v : g[u]) {
            if(vis[v] == Tt) continue;
            f[k][v] = f[k][u] + 1;
            vis[v] = Tt;
            q[t++] = v;
        }
    }
}
  
int main() {
#ifdef CX_TEST
    freopen("E:\\program--GG\\test_in.txt", "r", stdin);
    freopen("01.txt", "w", stdout);
#endif
    int n, m, Q, i, j, u, v;
    In(n), In(m);
    for(i = 0; i < m; i++) {
        In(u), In(v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    // sort(p.begin(), p.end());
    // p.erase(unique(p.begin(), p.end()), p.end());
    m = p.size();
    for(i = 0; i < m; i++) bfs(i, p[i]);
    In(Q);
    while(Q--) {
        In(u), In(v);
        j = d[u] + d[v] - 2 * d[lca(u, v)];
        for(i = 0; i < m; i++) j = min(j, f[i][u] + f[i][v]);
        Out.oi(j);
    }
    Debug("Time: %.3lfs\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}