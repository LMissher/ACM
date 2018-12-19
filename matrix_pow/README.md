# 湘潭大学2018程序设计竞赛G
https://www.nowcoder.com/acm/contest/105/G

给一个递推式，$F_i=F_{i-1}+F_{i-2}+i^3+i^2+i+1。F_1=1,F_0=0$。
问$F_n$是多少。
典型的用矩阵快速幂加速解决斐波那契递推式。
$F_{i+1}=F_i+F_{i-1}+(i+1)^3+(i+1)^2+(i+1)+1=F_i+F_{i-1}+i^3+4 \times i^2+6 \times i+4$。
构造一个$6$阶矩阵即可。

# hdu 5950 Recursive sequence
http://acm.hdu.edu.cn/showproblem.php?pid=5950

$F_1=a,F_2=b。F_n=F_{n-1}+2\times F_{n-2}+n^4$。
输入$n$，求$F_n$。
用二项式定理把 $n^4$ 拆开，就是裸的矩阵快速幂了。