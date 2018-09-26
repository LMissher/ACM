# 湘潭大学2018程序设计竞赛G
https://www.nowcoder.com/acm/contest/105/G

给一个递推式，F[i]=F[i-1]+F[i-2]+i^3+i^2+i+1。F[1]=1,F[0]=0。
问F[n]是多少。
典型的用矩阵快速幂加速解决斐波那契递推式。
F[i+1]=F[i]+F[i-1]+(i+1)^3+(i+1)^2+(i+1)+1=F[i]+F[i-1]+i^3+4*i^2+6*i+4。
构造一个6阶矩阵即可。

# hdu 5950 Recursive sequence
http://acm.hdu.edu.cn/showproblem.php?pid=5950

F[1]=a,F[2]=b。F[n]=F[n-1]+2*F[n-2]+n^4。
输入n，求F[n]。
用二项式定理把 n^4 拆开，就是裸的矩阵快速幂了。