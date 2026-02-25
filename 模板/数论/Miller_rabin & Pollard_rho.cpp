#include<iostream>
#include<cstdlib>
#include<ctime>
#define ll long long
using namespace std;
ll qmi(ll a,ll b,ll mod){
	ll ans=1;
	for(;b;b>>=1){
		if(b&1) ans=(__int128)ans*a%mod;
		a=(__int128)a*a%mod;
	}
	return ans;
}
bool check(ll a,ll n){
	ll b=n-1,t=0;
	while(b%2==0) b>>=1,t++;
	ll x1=qmi(a,b,n),x2;
	while(t--){
		x2=(__int128)x1*x1%n;
		if(x2==1&&x1!=1&&x1!=n-1) return 1;
		x1=x2;
	}
	if(x1!=1) return 1;
	return 0;
}
bool miller_rabin(ll n){
	if(n==2) return 1;
	if(n%2==0) return 0;
	int flag=0;
	for(int s=1;s<=50;s++){
		long long a=1ll*rand()*rand()%(n-1)+1;
		if(check(a,n)) return 0;
	}
	return 1;
}
ll fac[105],cnt;
ll gcd(ll a,ll b){
	return b?gcd(b,a%b):a;
}
ll pollad_rho(ll n){
	ll i=1,k=2;
	ll c=1ll*rand()*rand()%(n-1)+1;
	ll x=1ll*rand()*rand()%n;
	ll y=x,val=1; 
	while(1){
		i++;
		x=((__int128)x*x+c)%n;
		val=((__int128)val*abs(x-y))%n;
		if(!val) return n;
		if(i%127==0){
			ll d=gcd(val,n);
			if(d>1) return d;
		}
		if(i==k) {
			y=x,k<<=1;
			ll d=gcd(val,n);
			if(d>1) return d;
		}
	}
}
void findfac(ll n){
	if(miller_rabin(n)){
		fac[++cnt]=n;
		return;
	}
	ll p=n;
	while(p>=n) p=pollad_rho(p);
	findfac(p);
	findfac(n/p);
}
int main(){
	srand(time(0));
	int T;
	cin>>T;
	while(T--){
		long long n;
		scanf("%lld",&n);
		cnt=0;
		findfac(n);
		if(cnt==1) puts("Prime");
		else{
			long long ans=0;
			for(int i=1;i<=cnt;i++) ans=max(ans,fac[i]); 
			printf("%lld\n",ans);
		}
	}
	return 0;
}
