#define others
#ifdef poj
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <vector>
#endif // poj
#ifdef others
#include <bits/stdc++.h>
#endif // others
//#define file
#define all(x) x.begin(), x.end()
using namespace std;
const double eps = 1e-8;
int dcmp(double x) { if(fabs(x)<=eps) return 0; return (x>0)?1:-1;};
typedef long long LL;
typedef unsigned long long ULL;

void file() {
    freopen("out.txt", "r", stdin);
    freopen("out1.txt", "w", stdout);
}

namespace Solver {
    const LL maxn = 55000;
    stack<pair<LL*, LL> >stk;
    LL fa[maxn], sz[maxn];
    vector<LL> G[maxn];
    LL l[maxn*2], r[maxn*2], res[maxn*2];
    vector<LL> Mo[1111];
    LL block;
    LL ans = 0;
    void init() {
        for(LL i = 0; i < maxn; i++) fa[i] = i, sz[i] = 1, G[i].clear();
        for(LL i = 0; i < 1111; i++) Mo[i].clear();
        ans = block = 0;
        while(!stk.empty()) stk.pop();
    }
    LL find(LL x) {
        return x == fa[x]?x : find(fa[x]);
    }
    void goback() {
        while(!stk.empty()) {
            (*stk.top().first) = stk.top().second;
            stk.pop();
        }
    }

    void merge(LL x, LL y, LL f) {
        LL f1 = find(x), f2 = find(y);
        if(f1 != f2) {
            if(sz[f1] > sz[f2]) swap(f1, f2);
            if(f) stk.push({&fa[f1], fa[f1]});
            fa[f1] = f2;
            if(f) stk.push({&ans, ans});
            ans -= (sz[f1] * (sz[f1] - 1) / 2);
            ans -= (sz[f2] * (sz[f2] - 1) / 2);
            if(f) stk.push({&sz[f2], sz[f2]});
            sz[f2] += sz[f1];
            ans += (sz[f2] * (sz[f2]-1) / 2);
        }
    }

    void solve() {
        LL t, n, m, q;
        scanf("%lld", &t);
        while(t--) {
            init();
            scanf("%lld%lld%lld", &n, &m, &q);
            for(LL i = 1; i <= m; i++) {
                LL u, v; scanf("%lld%lld", &u, &v);
                G[u].push_back(v);
                G[v].push_back(u);
            }
            block = sqrt(n);
            for(LL i = 1; i <= q; i++) {
                scanf("%lld%lld", &l[i],&r[i]);
                LL L = (l[i]-1)/block, R = (r[i]-1)/block;
                if(L == R) {
                    for(LL j = l[i]; j <= r[i]; j++) {
                        for(LL v:G[j]) {
                            if(v >= l[i] && v <= r[i])
                                merge(j, v, 1);
                        }
                    }
                    res[i] = ans;
                    goback();
                } else
                    Mo[L].push_back(i);
            }
            for(LL i = 0; (i+1)*block<=n; i++) {
                sort(Mo[i].begin(), Mo[i].end(), [&](LL a, LL b) {return r[a] < r[b];});
                ans = 0;
                while(!stk.empty()) stk.pop();
                LL nl = block*(i+1), nr = nl - 1;
                for(LL _ = 1; _ <= n; _++) fa[_] = _, sz[_] = 1;

                for(LL j = 0; j < Mo[i].size(); j++) {
                    while(nr < r[Mo[i][j]]) {
                        nr ++;
                        for(LL v:G[nr]) {
                            if(v <= r[Mo[i][j]] && v >= nl)
                                merge(nr, v, 0);
                        }
                    }
                    for(LL p = l[Mo[i][j]]; p < nl; p++)
                        for(LL v:G[p])
                            if(v <= r[Mo[i][j]] && v >= l[Mo[i][j]])
                                merge(v, p, 1);
                    res[Mo[i][j]] = ans;
                    goback();
                    nl = block*(i+1);
                }
            }
            for(LL i = 1; i <= q; i++)
                printf("%lld\n", res[i]);
        }
    }
}

int main() {
//    file();
    Solver::solve();
    return 0;
}