#include<bits/stdc++.h>
#define N 200005
#define ll long long
#define mod 1000000007
#define inv2 500000004
#define inv6 166666668
using namespace std;
ll n,m;
ll v[N],p[N],cp;
ll s1[N],s2[N];
void shai(int n){
	p[0]=1;
	for(int i=2;i<=n;i++){
		if(!v[i]) {
			v[i]=p[++cp]=i;
			s1[cp]=(s1[cp-1]+i)%mod;
			s2[cp]=(s2[cp-1]+1ll*i*i)%mod;
		}
		for(int j=1;j<=cp;j++){
			if(v[i]<p[j]||i*p[j]>n) break;
			v[i*p[j]]=p[j];
		}
	}
}
ll g1[N],g2[N];
ll S1(ll n){
	return n*(n+1)%mod*inv2%mod;
}
ll S2(ll n){
	return n*(n+1)%mod*(n*2+1)%mod*inv6%mod;
}
ll b[N],id1[N],id2[N],tot;
int get(ll x){
	return x<=m?id1[x]:id2[n/x];
}
void calc(){
	for(ll l=1,r;l<=n;l=r+1){
		ll x=n/l;r=n/x;
		b[++tot]=x;
		g1[tot]=S1(x%mod)-1;
		g2[tot]=S2(x%mod)-1;
		if(x<=m) id1[x]=tot;
		else id2[n/x]=tot;
	}
	for(int j=1;j<=cp;j++)
		for(int i=1;i<=tot&&p[j]*p[j]<=b[i];i++){
			g1[i]=(g1[i]-p[j]*(g1[get(b[i]/p[j])]-s1[j-1])%mod+mod)%mod;
			g2[i]=(g2[i]-p[j]*p[j]%mod*(g2[get(b[i]/p[j])]-s2[j-1])%mod+mod)%mod;
		}
}
ll h(ll i,int j){
	if(p[j]>i) return 0;
	ll ans=((g2[get(i)]-g1[get(i)]-(s2[j]-s1[j]))%mod+mod)%mod;
	for(int k=j+1;k<=cp&&p[k]*p[k]<=i;k++)
		for(ll val=p[k];val<=i;val=val*p[k]) 
			ans=(ans+val%mod*(val%mod-1)%mod*(h(i/val,k)+(val!=p[k])))%mod;
	return ans;
}
int main(){
	cin>>n;
	m=sqrt(n);
	shai(m);
	calc();
	printf("%lld\n",(h(n,0)+1)%mod);
	return 0;
}
