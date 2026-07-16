#include<bits/stdc++.h>
#define N 1100005
#define mod 998244353
#define ll long long
using namespace std;
template<typename T> void read(T &x){
	x=0;int f=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) f=(c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	if(f) x=-x;
}
int n,M=1;
ll qmi(ll a,ll b){
	ll ans=1;
	for(;b;b>>=1,a=a*a%mod) if(b&1) ans=ans*a%mod;
	return ans;
}
ll f[N],g[N],f2[N];
int rev[N];
ll t1[N],t2[N],t3[N],t4[N],t5[N];
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
}
void convol(vector<ll> &a,vector<ll> &b,vector<ll> &c){
	int len=a.size()+b.size()-1,M=1;
	while(M<len) M<<=1;M<<=1;
	for(int i=0;i<M;i++) f[i]=g[i]=0;
	for(int i=0;i<a.size();i++) f[i]=a[i];
	for(int i=0;i<b.size();i++) g[i]=b[i];
	polymul(f,g,M);
	c.clear();
	for(int i=0;i<len;i++) c.push_back(f[i]);
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
void polyd(ll *f,int len){
	for(int i=0;i<len;i++) f[i]=f[i+1]*(i+1)%mod;
}
void polyj(ll *f,int len){
	for(int i=len;i>=1;i--) f[i]=f[i-1]*qmi(i,mod-2)%mod;
	f[0]=0;
}
void polyln(ll *f,int len){
	for(int i=0;i<len*2;i++) t3[i]=0;
	polyinv(f,t3,len);
	polyd(f,len);
	polymul(f,t3,len*2);
	polyj(f,len);
}
void polyexp(ll *f,ll *g,int M){
	g[0]=1;
	for(int len=2;len<=M;len<<=1){
		for(int i=0;i<len*2;i++) t4[i]=t5[i]=0;
		for(int i=0;i<len;i++) t5[i]=g[i];
		polyln(t5,len);
		for(int i=0;i<len;i++) t4[i]=(f[i]-t5[i]+(i==0)+mod)%mod;
		polymul(g,t4,len*2);
		for(int i=len;i<len*2;i++) g[i]=0;
	}
}
void polymi(ll *f,ll *g,int m,int M){
	for(int i=0;i<M;i++) g[i]=0;
	polyln(f,M);
	for(int i=0;i<M;i++) f[i]=f[i]*m%mod;
	polyexp(f,g,M);
}
void polysqrt(ll *f,ll *g,int M){
	ll inv2=qmi(2,mod-2);
	g[0]=1;
	for(int len=2;len<=M;len<<=1){
		for(int i=0;i<len*2;i++) t4[i]=t5[i]=0;
		for(int i=0;i<len;i++) t4[i]=g[i];
		polyinv(t4,t5,len);
		for(int i=0;i<len;i++) t4[i]=f[i];
		polymul(t4,t5,len*2);
		for(int i=0;i<len;i++) g[i]=(g[i]+t4[i])*inv2%mod;
	}
}

int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%lld",&f[i]);
	while(M<=n) M<<=1;
	polysqrt(f,g,M);
	for(int i=0;i<n;i++) cout<<g[i]<<" ";
	return 0;
}


