# codeforces 1051D Bicolorings
http://codeforces.com/contest/1051/problem/D

问你把一个两行n列的方格染成k个联通块一共有多少种方法。
因为第 i 列和第 i+1 列分别可以产生四种不同的组合，00、01、10、11。
那么我们设数组 dp[i][j][k] 。表示到第 i 列以第 k 个组合产生 j 个联通块。
直接dp即可。