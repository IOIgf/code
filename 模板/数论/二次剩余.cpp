#include<iostream>
#include<cstdlib>
#include<ctime>
#define ll long long
using namespace std;
ll n,p,t;
ll qmi(ll a,ll b){
	ll ans=1;
	for(;b;b>>=1,a=a*a%p)
		if(b&1) ans=ans*a%p;
	return ans;
}
struct C{
	ll x,i;
};
C operator +(C a,C b){
	return {(a.x+b.x)%p,(a.i+b.i)%p};
}
C operator *(C a,C b){
	return {(a.x*b.x+a.i*b.i%p*t)%p,(a.i*b.x+a.x*b.i)%p};
}
ll qmi2(C a,ll b){
	C ans={1,0};
	for(;b;b>>=1,a=a*a) if(b&1) ans=ans*a;
	return ans.x;
}
int main(){
	srand(time(0));
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%lld%lld",&n,&p);
		if(qmi(n,(p-1)/2)==p-1) puts("Hola!");
		else if(n==0) puts("0");
		else{
			ll r=1ll*rand()*rand()%p*rand()%p;
			t=(r*r%p-n+p)%p;
			while(!t||qmi(t,(p-1)/2)==1){
				r=1ll*rand()*rand()%p*rand()%p;
				t=(r*r%p-n+p)%p;
			}
			ll rt1=qmi2({r,1},(p+1)/2);
			ll rt2=p-rt1;
			if(rt1>rt2) swap(rt1,rt2);
			printf("%lld %lld\n",rt1,rt2);
		}
	}
	return 0;
}
