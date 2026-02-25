#include<bits/stdc++.h>
#define N 1100005
#define mod 998244353
#define ll long long
using namespace std;
int n,k,M=1;
ll qmi(ll a,ll b){
	ll ans=1;
	for(;b;b>>=1,a=a*a%mod) if(b&1) ans=ans*a%mod;
	return ans;
}
ll a[N];
ll f[N],f2[N],g[N],h[N],tmp[N];
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
void polymod(ll *g,ll *h){
	int n=2*k-2,m=k;
	reverse(g,g+n+1);
	for(int i=0;i<M;i++) h[i]=g[i];
	for(int i=n-m+1;i<M;i++) h[i]=0;
	NTT(h,0,M);
	for(int i=0;i<M;i++) h[i]=h[i]*f2[i]%mod;
	NTT(h,1,M);
	for(int i=n-m+1;i<M;i++) h[i]=0;
	reverse(h,h+n-m+1);
	reverse(g,g+n+1);
	polymul(h,f,M);
	for(int i=m;i<M;i++) h[i]=0;
	for(int i=0;i<m;i++) h[i]=(g[i]-h[i]+mod)%mod;
}  
void qpow(int n){
	g[0]=1,h[1]=1;
	for(;n;n>>=1){
		if(n&1){
			for(int i=0;i<M;i++) tmp[i]=h[i];
			polymul(tmp,g,M);
			polymod(tmp,g);
		}
		for(int i=0;i<M;i++) tmp[i]=h[i];
		polymul(tmp,h,M);
		polymod(tmp,h);
	}
}
int main(){
	scanf("%d%d",&n,&k);
	while(M<=k) M<<=1;M<<=1;
	for(int i=1;i<=k;i++) {
		scanf("%lld",&f[i]);
		f[i]=(mod-f[i]%mod)%mod;
	}
	f[0]=1;
	polyinv(f,f2,M);
	for(int i=k-1;i<M;i++) f2[i]=0;
	NTT(f2,0,M);
	reverse(f,f+k+1);
	for(int i=0;i<k;i++) {
		scanf("%lld",&a[i]);
		a[i]=(a[i]%mod+mod)%mod;
	}
	qpow(n);
	ll ans=0;
	for(int i=0;i<k;i++) ans=(ans+a[i]*g[i])%mod;
	printf("%lld\n",ans);
	return 0;
}



