#include<bits/stdc++.h>
#define ll long long
#define mod 1000000007
using namespace std;
int n,m,ty;
ll a[305][305];
ll qmi(ll a,ll b){
	ll ans=1;
	for(;b;b>>=1,a=a*a%mod) if(b&1) ans=ans*a%mod;
	return ans;
}
ll det(){
	ll ans=1;
	for(int i=2;i<=n;i++){
		int p=0;
		for(int j=i;j<=n;j++) if(a[j][i]) p=j;
		if(!p) return 0;
		if(p!=i) ans*=-1;
		for(int j=1;j<=n;j++) swap(a[i][j],a[p][j]);
		for(int j=i+1;j<=n;j++){
			ll div=a[j][i]*qmi(a[i][i],mod-2)%mod;
			for(int k=1;k<=n;k++) a[j][k]=(a[j][k]-a[i][k]*div%mod+mod)%mod;
		}
	}
	for(int i=2;i<=n;i++) ans=ans*a[i][i]%mod;
	return (ans+mod)%mod;
}
int main(){
	scanf("%d%d%d",&n,&m,&ty);
	for(int i=1;i<=m;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		if(ty==0){
			a[x][y]=(a[x][y]-z+mod)%mod;
			a[y][x]=(a[y][x]-z+mod)%mod;
			a[x][x]=(a[x][x]+z)%mod;
			a[y][y]=(a[y][y]+z)%mod;
		}else{
			a[x][y]=(a[x][y]-z+mod)%mod;
			a[y][y]=(a[y][y]+z)%mod;
		}
	}
	printf("%lld\n",det());
	return 0;
}

/*

无向图：
邻接矩阵-度数矩阵
有向图：
外向树：入度矩阵
内向树：出度矩阵

删一行、一列求行列式 

*/
