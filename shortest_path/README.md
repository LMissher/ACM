# codeforces 1051F
http://codeforces.com/contest/1051/problem/F

给一副图，图中的边最多比点多20条。给q次询问，每次询问两点的最短路。
随便弄一个生成树，然后求出两点在树上的距离。
把非树边的两端点保存然后求分别求一次最短路。
然后以所有非树边端点的最短距离更新即可。

# wannafly_day1_J
http://newoj.acmclub.cn/contests/1389/problem/9

和上一题同理。

# wannafly_day3_I
https://www.nowcoder.com/acm/contest/203/I

多源最短路。  
在一幅无向图中给出点集，问点集中的每个点到其他点的最短距离是多少。  
把点集里的点都做为源点，每个点都再增加一个祖先属性，表示这个点被哪个源点的最短路所更新。  
然后跑一次多源最短路即可。  