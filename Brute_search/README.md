# hdu5952 Counting Cliques
http://acm.hdu.edu.cn/showproblem.php?pid=5952

给一幅图，求指定点个数的完全图有多少个。
点100个，边1000条，都很少，考虑爆搜。
建图的时候由完全图的性质只用把编号小的向编号大的连边。
然后搜索的时候直接暴力查找，遇到满足条件的完全图就答案+1并返回。

# 2017Tsukuba_K
https://vjudge.net/contest/259596#problem/J

求一幅简单图里有多少简单环。  
先进行缩点，把度数为1的点用拓扑排序直接缩掉，度数为2的链上的点可以缩成一个三元环。  
把缩完点后的图直接爆搜有多少环就可以。  
具体就是把每一条边从图里删去，然后看从这条边的u到v有多少条到达的路径，总的所有路径数就是答案。  

# codeforces1063B Labyrinth
http://codeforces.com/problemset/problem/1063/B

一幅网格图里有许多路障，限制你只能向左走多少步与向右走多少步，上下不限，问所有可能到达的格子总数是多少。  
BFS即可。注意搜到一个点时要更新它的状态为最大值即可。  

# codeforces1070A Find a Number
http://codeforces.com/problemset/problem/1070/A

给两个数$d、s$,问能不能找到一个数能整除$d$且其数位和为$s$。  
因为$d$的范围是$0$到$500$,$s$的范围是$0$到$5000$,可以考虑爆搜。  
如果两个数字对$d$的余数相同且其数位和相同可以看作同一个$bfs$状态。  
那么总的状态只有$500\times5000$，直接搜索即可。