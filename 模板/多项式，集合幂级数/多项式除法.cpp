#include<bits/stdc++.h>
#define N 1100005
#define mod 998244353
#define ll long long
using namespace std;
int n,m,M=1;
ll qmi(ll a,ll b){
	ll ans=1;
	for(;b;b>>=1,a=a*a%mod) if(b&1) ans=ans*a%mod;
	return ans;
}
ll f[N],g[N],f2[N],g2[N],tmp[N];
int rev[N];
ll t1[N],t2[N];
void NTT(ll *f,int flag,int M){
	for(int i=0;i<M;i++){
		rev[i]=rev[i>>1]>>1;
		if(i&1) rev[i]|=M/2;
		if(i<rev[i]) swap(f[i],f[rev[i]]);
	}
	for(int step=2;step<=M;step<<=1){
		ll wn=qmi(3,(mod-1)/step);
		for(int k=0;k<M;k+=step){
			ll w=1;
			for(int i=k;i<k+step/2;i++){
				ll a=f[i],b=w*f[i+step/2]%mod;
				f[i]=(a+b)%mod;
				f[i+step/2]=(a-b+mod)%mod;
				w=w*wn%mod;
			}
		}
	}
	if(flag){
		reverse(f+1,f+M);
		ll inv=qmi(M,mod-2);
		for(int i=0;i<M;i++) f[i]=f[i]*inv%mod;
	}
}
void polymul(ll *f,ll *g,int M){
	NTT(f,0,M);
	NTT(g,0,M);
	for(int i=0;i<M;i++) f[i]=f[i]*g[i]%mod;
	NTT(f,1,M);
	NTT(g,1,M);
}
void polyinv(ll *f,ll *g,int M){
	g[0]=qmi(f[0],mod-2);
	for(int len=2;len<=M;len<<=1){
		for(int i=0;i<len*2;i++) t1[i]=t2[i]=0;
		for(int i=0;i<len;i++) t1[i]=f[i];
		for(int i=0;i<len/2;i++) t2[i]=g[i];
		NTT(t1,0,len*2);
		NTT(t2,0,len*2);
		for(int i=0;i<len*2;i++) t2[i]=t2[i]*(2-t1[i]*t2[i]%mod+mod)%mod;
		NTT(t2,1,len*2);
		for(int i=0;i<len;i++) g[i]=t2[i];
	}
}
int main(){
	scanf("%d%d",&n,&m);
	while(M<=n) M<<=1;M<<=1;
	for(int i=0;i<=n;i++) scanf("%lld",&f[i]);
	for(int i=0;i<=m;i++) scanf("%lld",&g[i]);
	reverse(f,f+n+1);
	reverse(g,g+m+1);
	polyinv(g,f2,M);
	for(int i=n-m+1;i<M;i++) f2[i]=0;
	polymul(f2,f,M);
	for(int i=n-m+1;i<M;i++) f2[i]=0;
	reverse(f2,f2+n-m+1);
	reverse(f,f+n+1);
	reverse(g,g+m+1);
	for(int i=0;i<n-m+1;i++) g2[i]=f2[i];
	polymul(g2,g,M);
	for(int i=0;i<m;i++) g2[i]=(f[i]-g2[i]+mod)%mod;
	for(int i=0;i<n-m+1;i++) printf("%lld ",f2[i]);
	puts("");
	for(int i=0;i<m;i++) printf("%lld ",g2[i]);
	return 0;
}


