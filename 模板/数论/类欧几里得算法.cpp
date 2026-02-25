#include<bits/stdc++.h>
#define ll long long
#define mod 998244353
#define inv2 499122177
#define inv6 166374059
using namespace std;
struct node{
	ll f,g,h;
};
ll S1(ll n){
	return n*(n+1)%mod*inv2%mod;
}
ll S2(ll n){
	return n*(n+1)%mod*(n*2+1)%mod*inv6%mod;
}
node calc(ll a,ll b,ll c,ll n){
	ll d1=a/c,d2=b/c;
	if(a==0) return {d2*(n+1)%mod,d2*d2%mod*(n+1)%mod,S1(n)*d2%mod};
	if(a>=c||b>=c){
		node val=calc(a%c,b%c,c,n),ans;
		ll f=val.f,g=val.g,h=val.h;
		ans.f=(f+d1*S1(n)%mod+d2*(n+1)%mod)%mod;
		ans.g=(g+d1*d1%mod*S2(n)%mod+d2*d2%mod*(n+1)%mod+2*d1*d2%mod*S1(n)%mod+2*f*d2%mod+2*h*d1%mod)%mod;
		ans.h=(h+d1*S2(n)%mod+d2*S1(n)%mod)%mod;
		return ans;
	}
	ll m=(a*n+b)/c;
	node val=calc(c,c-b-1,a,m-1),ans;
	ll f=val.f,g=val.g,h=val.h;
	ans.f=(n*m-f+mod)%mod;
	ans.g=((n*m%mod*(m+1)%mod-2*h-2*f-ans.f)%mod+mod)%mod;
	ans.h=((m*S1(n)%mod-inv2*g%mod-inv2*f%mod)%mod+mod)%mod;
	return ans;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		ll n,a,b,c;
		scanf("%lld%lld%lld%lld",&n,&a,&b,&c);
		node ans=calc(a,b,c,n);
		printf("%lld %lld %lld\n",ans.f,ans.g,ans.h);
	}
	return 0;
}
