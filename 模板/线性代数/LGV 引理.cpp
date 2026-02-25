#include<iostream>
#include<cstring>
#define mod 998244353
#define ll long long
#define N 205
using namespace std;
int n,m,a[N],b[N];
ll qmi(ll a,ll b){
	ll ans=1;
	for(;b;b>>=1,a=a*a%mod) if(b&1) ans=ans*a%mod;
	return ans;
}
ll c[N][N],fac[2000005],inf[2000005];
ll C(int n,int m){
	if(n<m)return 0;
	return fac[n]*inf[m]%mod*inf[n-m]%mod;
}
ll gauss(){
	ll ans=1;
	for(int i=1;i<=m;i++){
		int p=0;
		for(int j=i;j<=m;j++) if(c[j][i]) p=j;
		if(p!=i) ans*=-1;
		if(!p) return 0;
		for(int j=1;j<=m;j++) swap(c[i][j],c[p][j]);
		for(int j=i+1;j<=m;j++){
			ll rate=qmi(c[i][i],mod-2)*c[j][i]%mod;
			for(int k=1;k<=m;k++) c[j][k]=(c[j][k]-rate*c[i][k])%mod;
		}
	}
	for(int i=1;i<=m;i++) ans=ans*c[i][i]%mod;
	return (ans+mod)%mod;
}
int main(){
	fac[0]=inf[0]=1;
	for(int i=1;i<=2000000;i++) {
		fac[i]=fac[i-1]*i%mod;
		inf[i]=qmi(fac[i],mod-2);
	}
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		memset(c,0,sizeof(c));
		for(int i=1;i<=m;i++) scanf("%d%d",&a[i],&b[i]);
		for(int i=1;i<=m;i++)
			for(int j=1;j<=m;j++) 
				if(a[i]<=b[j]) c[i][j]=C(b[j]-a[i]+n-1,n-1);
		printf("%lld\n",gauss());
	}
	return 0;
}
