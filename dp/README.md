# codeforces 1051D Bicolorings
http://codeforces.com/contest/1051/problem/D

问你把一个两行n列的方格染成k个联通块一共有多少种方法。  
因为第 i 列和第 i+1 列分别可以产生四种不同的组合，00、01、10、11。  
那么我们设数组 dp[i][j][k] 。表示到第 i 列以第 k 个组合产生 j 个联通块。  
直接dp即可。  

# hdu3401 Trade
http://acm.hdu.edu.cn/showproblem.php?pid=3401

单调队列优化dp  
形如 dp[i][j] = dp[r][k] + x * k + c 的式子皆可用单调队列优化  
这道题问给 t 天，每天有能买入卖出股票的数量，以及买入卖出股票的价格，交易每隔 w + 1 天进行  
这题很容易想到用 dp[i][j] ，第 i 天有 j 只股票赚的钱  
转移方程为
dp[i][j] = max(dp[i-1][j], max( dp[r][k] - API[i] * ( j - k ) | (j>k) , dp[r][k] + BPI[i] * ( k - j )  | (k>j)) )  
其中第一种情况是这一天什么都不做,
第二种情况是找到1<=r<=i-w-1中有k只股票再买一些能达到j只股票,
第三种是找到1<=r<=i-w-1中有k只股票再卖一些能达到j只股票  
但显然这样的复杂度是t * p * p的  
考虑dp[i][j]>=dp[i-1][j]恒成立，所有只用考虑 r = i-w-1 的情况即可。  
化简式子得到 买入: (dp[i-w-1][k]+API[i] * k)-API[i] * j  卖出: (dp[i-w-1][k]+BPI[i] * k)-BPI[i] * j  
所以只用找到最大的括号里的式子即可  
枚举k与j，可以同时枚举，因为如果k>j则买入必不可能，卖出同理  
单调队列维护之前的最大值即可  

# NOI2010 fenghuochuandi
http://www.joyoi.cn/problem/tyvj-1313

给n个数，要求每m个数必须点燃一把火，每个点点燃的代价不同  
问怎样点的代价最小  
想到 dp 方程为 dp[i] = min( dp[j] + val[i] ) | i-m <= j <= i-1  
但这样做复杂度是 n^2 的，不可接受  
考虑用单调队列优化即可  
注意前 m 个是必须要点燃一个，后 m 个同理  

# hdu3507 Print Article
http://acm.hdu.edu.cn/showproblem.php?pid=3507

斜率优化dp  
这道题问给n个数，要你用最小的代价把n个数分成一些区间，代价是区间数和的平方加M的和  
得到递推式 dp[i] = min( dp[j] + (sum[i] - sum[j])^2 + M )  
假设选择的点j优于k，那么 dp[j] + (sum[i] - sum[j])^2 + M < dp[k] + (sum[i] - sum[k])^2 + M  
化简得到 (dp[j] + sum[j]^2 -dp[k] -sum[k]^2 ) / 2 * ( sum[j] - sum[k] ) < sum[i]  
令 F[x] = dp[x] + sum[x]^2，则上式为 (F[j] - F[k]) / 2 * (sum[j]-sum[k]) < sum[i]  
类似于一个斜率的式子，所以得到结果点对(i,j)满足上式则 i 更优于 j  
且sum[i]是前缀和单调递增所以两点只要满足则之后也一定满足  
到一个点时找到当前最优的点更新结果即可  
如果先后三个点k，j，i，且(i,j)的式子结果小于(j,k)，那么j点必不可能是最优点，舍弃  
用单调队列维护一个下凸的点集  

# hdu 5956 The Elder
http://acm.hdu.edu.cn/showproblem.php?pid=5956

树上斜率优化dp  
有一颗树，问从树上所有节点到根节点的代价中最大的那个。  
每个节点到根节点的代价为把距离划分为 m 段，每段距离的平方和再加上 m * p，p为常数。  
典型的斜率优化，把根节点设为出发节点，初始价值为p，那么子孙节点的递推式为 dp[i] = min( dp[j] + (len[i] - len[j])^2 + P )  
只需要在dfs进入某个节点时保存原有的头尾节点在出节点时恢复即可。  