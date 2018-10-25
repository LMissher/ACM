# codeforces1066E Binary Numbers AND Sum
http://codeforces.com/problemset/problem/1066/E

给两个长度为 $2\times10^{5}$ 的 $01$ 串 $a、b$ 。  
重复执行以下操作。  
先 $ans+=a&b$ 再 $b\div2$ 。  
求最后的答案是多少。  
先对$a$的所有位数求到当前位数前面所有的 $1$ 的十进制之和。  
对于$b$中的每一位数对于要和$a$中的哪些数字与是确定的，直接算贡献即可。  