# 2017Tsukuba H
https://vjudge.net/contest/259596#problem/G

有个人有两个课程，每个课程有很多个作业，每个作业有开始日期与截至日期。  
每天只能选择一个课程的一个作业做。问这个人最多与最少可以完成多少作业。  
最多的话贪心的去找到每天可以做的所有作业中截止日期最近的那个即可。  
最少的话将日期拆点表示日期只能用一次，一种作业与源点连接容量为 $1$，然后与日期一边 $[start,deadline]$ 连接容量为 $1$。  
另一种作业与汇点连接容量为 $1$，然后与日期另一边 $[start,deadline]$ 连接容量为 $1$。  
因为当日期只与一个种类作业连接或者没有作业连接时这一天都可以没作业做。  
相当于寻找一个最小的割集让图不连通也就是所有日期都最多只有一个种类的作业连接，找不到作业去做。  

# 2017Daejeon E


给出一个有 $n$ 个点 $m$ 条边的图，每条边有一个边权。
问要使第 $i$ 条边成为图的最小生成树的一条边最少要删掉多少条边，求出每条边的对应答案的和。  
枚举边 $i$ ，找出那些边权小于 $i$ 的边权的边，这些边都是网络流里的边，然后以连接 $i$ 的两个点为源点和汇点跑网络流求最小割。