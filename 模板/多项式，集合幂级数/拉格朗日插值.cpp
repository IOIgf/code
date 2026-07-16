#include<iostream>
#define N 2005
#define mod 998244353
using namespace std;
int n,k;
int x[N],y[N];
long long qmi(long long a,long long b){
	long long ans=1;
	for(;b;b>>=1){
		if(b&1) ans=ans*a%mod; 
		a=a*a%mod;
	}
	return ans;
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d%d",&x[i],&y[i]);
	long long ans=0;
	for(int i=1;i<=n;i++){
		long long val=y[i];
		for(int j=1;j<=n;j++){
			if(i==j) continue;
			val=val*(k-x[j])%mod*qmi(x[i]-x[j],mod-2)%mod;
		}
		ans=(ans+val+mod)%mod;
	}
	printf("%lld\n",ans);
	return 0;
}
