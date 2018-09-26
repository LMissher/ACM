#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 2147493647;
int _;
ll n,a,b;
struct mat
{
    ll a[8][8];
    mat(){
        memset(a,0,sizeof(a));
    }
    void init(){
        for(int i=0;i<7;i++) a[i][i]=1;
    }
    mat operator * (const mat & t)const{
        mat tmp;
        for(int i=0;i<7;i++)
            for(int j=0;j<7;j++)
                for(int k=0;k<7;k++)
                    tmp.a[i][j]=(tmp.a[i][j]+a[i][k]*t.a[k][j]%mod)%mod;
        return tmp;
    }
};
mat matrix_pow(mat x,ll k){
    mat ans,res;res=x;
    ans.init();
    while(k){
        if(k&1) ans=ans*res;
        res=res*res;
        k>>=1;
    }
    return ans;
}
int main(){
    mat x;
    x.a[0][0]=1ll,x.a[0][1]=2ll,x.a[0][2]=1ll,x.a[0][3]=4ll,x.a[0][4]=6ll,x.a[0][5]=4ll,x.a[0][6]=1ll;
    x.a[1][0]=1ll;
    x.a[2][2]=1ll,x.a[2][3]=4ll,x.a[2][4]=6ll,x.a[2][5]=4ll,x.a[2][6]=1ll;
    x.a[3][3]=1ll,x.a[3][4]=3ll,x.a[3][5]=3ll,x.a[3][6]=1ll;
    x.a[4][4]=1ll,x.a[4][5]=2ll,x.a[4][6]=1ll;
    x.a[5][5]=1ll,x.a[5][6]=1ll;
    x.a[6][6]=1ll;
    scanf("%d",&_);
    while(_--){
        scanf("%lld%lld%lld",&n,&a,&b);
        if(n==1){
            printf("%lld\n",a);
            continue;
        }
        if(n==2){
            printf("%lld\n",b);
            continue;
        }
        mat y=matrix_pow(x,n-2ll);
        printf("%lld\n",((((((y.a[0][0]*b%mod+y.a[0][1]*a%mod)%mod+y.a[0][2]*16ll%mod)%mod+y.a[0][3]*8ll%mod)%mod+y.a[0][4]*4ll%mod)%mod+y.a[0][5]*2ll%mod)%mod+y.a[0][6])%mod);
    }
    return 0;
}