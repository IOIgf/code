#include<bits/stdc++.h>
#define ll long long 
#define mod 1000000007
#define N 10000005
using namespace std;
const ll inv2=500000004,inv6=166666668;
ll n,ans;
ll S2(ll n){
	return n%mod*((n+1)%mod)%mod*((n*2+1)%mod)%mod*inv6%mod;
}
ll S1(ll n){
	return n%mod*((n+1)%mod)%mod*inv2%mod;
}
int v[N],p[N],cp;
ll f[N],phi[N];
void euler(int n){
	phi[1]=1;
	for(int i=2;i<=n;i++){
		if(!v[i]) v[i]=p[++cp]=i,phi[i]=i-1;
		for(int j=1;j<=cp;j++){
			if(v[i]<p[j]||i*p[j]>n) break;
			v[i*p[j]]=p[j];
			if(i%p[j]==0) phi[i*p[j]]=phi[i]*p[j];
			else phi[i*p[j]]=phi[i]*(p[j]-1);
		}
	}
}
ll du(ll m){
	if(m<N) return phi[m];
	if(f[n/m]) return f[n/m];
	ll ans=S2(m);
	for(ll l=2,r;l<=m;l=r+1){
		r=m/(m/l);
		ans=(ans-(S1(r)-S1(l-1))*du(m/l)%mod+mod)%mod;
	}
	return f[n/m]=ans;
}
vector<ll> p2[100005],h[100005];
void dfs(int x,ll val,ll now){
	if((double)p[x]*p[x]*val>n) return;
	for(int c=2;c<p2[x].size();c++){
		if((double)val*p2[x][c]>n) break;
		ans=(ans+now*h[x][c]%mod*du(n/val/p2[x][c]))%mod;
		dfs(x+1,val*p2[x][c],now*h[x][c]%mod);
	}
	dfs(x+1,val,now);
}
int main(){
	cin>>n;
	euler(N-1);
	for(int i=1;i<N;i++) phi[i]=(phi[i-1]+phi[i]*i)%mod;
	ans=du(n);
	for(int j=1;1ll*p[j]*p[j]<=n;j++){
		p2[j].push_back(1);
		h[j].push_back(1);
		ll c=1,val=p[j];
		while(val<=n){
			p2[j].push_back(val);
			ll val2=val%mod*((val-1)%mod)%mod;
			for(int i=1;i<=c;i++) val2=(val2-h[j][c-i]*(p2[j][i]%mod)%mod*(p2[j][i-1]*(p[j]-1)%mod)%mod+mod)%mod;
			h[j].push_back(val2);
			val*=p[j],c++;
		}
	}
	dfs(1,1,1);
	printf("%lld\n",ans);
	return 0;
}

