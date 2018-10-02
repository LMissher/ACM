# codeforces 1042D
http://codeforces.com/problemset/problem/1042/D

给 n 个数 ，问有多少区间满足 sigma(val[i]) < t ，相当于问前缀和 sum[r] - sum[l] < t 的 r 与 l 有多少对。  
转化为求 sum[r] - t < sum[l] 对数。  
用权值树状数组或者权值线段树都可以维护。  
每次插入一个数字之前看 sum[i] - t 之前有多少数字，然后再把 sum[i] 插入。  
注意最开始得有一个 sum[0] = 0 ，sum[i] - sum[0] 表示从 i 到 1 这个区间。   