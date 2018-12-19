# codeforces 1051D Bicolorings
http://codeforces.com/contest/1051/problem/D

问你把一个两行 $n$ 列的方格染成 $k$ 个联通块一共有多少种方法。  
因为第 $i$ 列和第 $i+1$ 列分别可以产生四种不同的组合，$00、01、10、11$。  
那么我们设数组 $dp[i][j][k]$ 。表示到第 $i$ 列以第 $k$ 个组合产生 $j$ 个联通块。  
直接dp即可。  

# hdu3401 Trade
http://acm.hdu.edu.cn/showproblem.php?pid=3401

单调队列优化$dp$  
形如 $dp[i][j] = dp[r][k] + x \times k + c$ 的式子皆可用单调队列优化  
这道题问给 $t$ 天，每天有能买入卖出股票的数量，以及买入卖出股票的价格，交易每隔 $w + 1$ 天进行  
这题很容易想到用 $dp[i][j]$ ，第 $i$ 天有 $j$ 只股票赚的钱  
转移方程为
$dp[i][j] = max(dp[i-1][j], max( dp[r][k] - API[i] \times ( j - k ) | (j>k) , dp[r][k] + BPI[i] \times ( k - j )  | (k>j)) )$  
其中第一种情况是这一天什么都不做,
第二种情况是找到$1 \le r \le i-w-1$中有 $k$ 只股票再买一些能达到 $j$ 只股票,
第三种是找到 $1 \le r \le i-w-1$中有 $k$ 只股票再卖一些能达到 $j$ 只股票  
但显然这样的复杂度是 $t \times p \times p$的  
考虑$dp[i][j] \ge dp[i-1][j]$恒成立，所有只用考虑 $r = i-w-1$ 的情况即可。  
化简式子得到 买入: $(dp[i-w-1][k]+API[i] \times k)-API[i] \times j$  卖出: $(dp[i-w-1][k]+BPI[i] \times k)-BPI[i] \times j$  
所以只用找到最大的括号里的式子即可  
枚举 $k$ 与 $j$ ，可以同时枚举，因为如果 $k > j$ 则买入必不可能，卖出同理  
单调队列维护之前的最大值即可  

# NOI2010 fenghuochuandi
http://www.joyoi.cn/problem/tyvj-1313

给 $n$ 个数，要求每 $m$ 个数必须点燃一把火，每个点点燃的代价不同  
问怎样点的代价最小  
想到 $dp$ 方程为 $dp[i] = min( dp[j] + val[i] ) | i-m \le j \le i-1$  
但这样做复杂度是 $n^2$ 的，不可接受  
考虑用单调队列优化即可  
注意前 $m$ 个是必须要点燃一个，后 $m$ 个同理  

# hdu3507 Print Article
http://acm.hdu.edu.cn/showproblem.php?pid=3507

斜率优化$dp$  
这道题问给 $n$ 个数，要你用最小的代价把 $n$ 个数分成一些区间，代价是区间数和的平方加 $M$ 的和  
得到递推式 $dp[i] = min( dp[j] + (\sum_{1}^i{val} - \sum_{1}^j{val})^2 + M )$  
假设选择的点 $j$ 优于 $k$，那么 $dp[j] + (\sum_{1}^i{val} - \sum_{1}^j{val})^2 + M < dp[k] + (\sum_{1}^i{val} - \sum_{1}^k{val})^2 + M$  
化简得到 $(dp[j] + (\sum_{1}^j{val})^2 - dp[k] - (\sum_{1}^k{val})^2 ) \div 2 \times ( \sum_{1}^j{val} - \sum_{1}^k{val} ) < \sum_{1}^i{val}$  
令 $F[x] = dp[x] + (\sum_{1}^x{val})^2$，则上式为 $(F[j] - F[k]) \div 2 \times (\sum_{1}^j{val} - \sum_{1}^k{val}) < \sum_{1}^i{val}$  
类似于一个斜率的式子，所以得到结果点对 $(i,j)$ 满足上式则 $i$ 更优于 $j$  
且 $\sum_{1}^i{val}$ 是前缀和单调递增所以两点只要满足则之后也一定满足  
到一个点时找到当前最优的点更新结果即可  
如果先后三个点$k$，$j$，$i$，且$(i,j)$的式子结果小于$(j,k)$，那么$j$点必不可能是最优点，舍弃  
用单调队列维护一个下凸的点集  

# hdu 5956 The Elder
http://acm.hdu.edu.cn/showproblem.php?pid=5956

树上斜率优化$dp$  
有一颗树，问从树上所有节点到根节点的代价中最大的那个。  
每个节点到根节点的代价为把距离划分为 $m$ 段，每段距离的平方和再加上 $m \times p$，$p$为常数。  
典型的斜率优化，把根节点设为出发节点，初始价值为$p$，那么子孙节点的递推式为 $dp[i] = min( dp[j] + (len[i] - len[j])^2 + P )$  
只需要在 $dfs$ 进入某个节点时保存原有的头尾节点在出节点时恢复即可。  

# codeforces 1042F
http://codeforces.com/problemset/problem/1042/F

给一颗树，问最少分为几个联通块让每个联通块里的叶子节点的距离都不超过 $k$ 。  
考虑从下向上的 $dp$ ，每个节点向上一个节点返回当前还存在的最深的叶子节点。  
如果在当前节点下的叶节点的最大值与次大值之和大于k则让最大值点自成一个联通块，反复直到不满足条件或者只剩一个叶节点。  
只用向上返回最深的叶节点深度即可，因为最深的点与祖先节点的其他子孙节点不兼容要么删去这个最深的点及这个子树下可能其他点要么直接删去整个这个子树下的所有叶节点，所以让最深点代替整个子树的叶节点即可。  


# codeforces 1076E
http://codeforces.com/contest/1076/problem/E

给出一颗带权树，初始权值都为 $0$ 。定义询问三元组 $(x,y,d)$ ，表示给节点 $x$ 子树中距离节点 $x$ 不超过 $y$ 的所有节点加上 $d$ 。  
问最后所有节点的权值。  
考虑 $dfs$ 时差分，在进入一个祖先节点时将以其为 $x$ 的询问都加进 $dfs$ 的值中再加到 $dep[dx+y]$ 上当遍历到子树里的此深度时将其减去。  
再退出祖先节点时将其所有询问从 $dep[dx+y]$ 里退出即可。  