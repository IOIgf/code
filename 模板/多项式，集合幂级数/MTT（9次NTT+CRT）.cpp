#include<bits/stdc++.h>
#define N 300005
#define ll long long
#define LL __int128
using namespace std;
template<typename T> void read(T &x){
	x=0;int f=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) f=(c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	if(f) x=-x;
}
ll qmi(ll a,ll b,ll mod){
	a%=mod;
	ll ans=1;
	for(;b;b>>=1,a=a*a%mod) if(b&1) ans=ans*a%mod;
	return ans;
}
int rev[N];
void NTT(ll *f,int M,int flag,int mod){
	for(int i=0;i<M;i++){
		rev[i]=rev[i>>1]>>1;
		if(i&1) rev[i]+=M/2;
		if(i<rev[i]) swap(f[i],f[rev[i]]);
	}
	for(int step=2;step<=M;step<<=1){
		ll wn=qmi(3,(mod-1)/step,mod);
		for(int k=0;k<M;k+=step){
			ll w=1;
			for(int i=k;i<k+step/2;i++){
				ll a=f[i],b=f[i+step/2]*w%mod;
				f[i]=(a+b)%mod;
				f[i+step/2]=(a-b+mod)%mod;
				w=w*wn%mod;
			}
		}
	}
	if(flag){
		reverse(f+1,f+M);
		ll inv=qmi(M,mod-2,mod);
		for(int i=0;i<M;i++) f[i]=f[i]*inv%mod;
	}
}
void polymul(ll *f,ll *g,int M,int mod){
	NTT(f,M,0,mod);
	NTT(g,M,0,mod);
	for(int i=0;i<M;i++) f[i]=f[i]*g[i]%mod;
	NTT(f,M,1,mod);
}
const int mod1=998244353,mod2=1004535809,mod3=469762049;
ll f1[N],f2[N],f3[N],g1[N],g2[N],g3[N];
void MTT(ll *f,ll *g,int M,int mod){
	for(int i=0;i<M;i++) {
		f1[i]=f2[i]=f3[i]=f[i];
		g1[i]=g2[i]=g3[i]=g[i];
	}
	polymul(f1,g1,M,mod1);
	polymul(f2,g2,M,mod2);
	polymul(f3,g3,M,mod3);
	LL MOD=(LL)mod1*mod2*mod3;
	ll M1=(ll)mod2*mod3,inv1=qmi(M1,mod1-2,mod1);
	ll M2=(ll)mod1*mod3,inv2=qmi(M2,mod2-2,mod2);
	ll M3=(ll)mod1*mod2,inv3=qmi(M3,mod3-2,mod3);
	for(int i=0;i<M;i++)
		f[i]=((LL)f1[i]*M1*inv1+(LL)f2[i]*M2*inv2+(LL)f3[i]*M3*inv3)%MOD%mod;
}

int n,m,M=1,mod;
ll f[N],g[N];
int main(){
	read(n),read(m),read(mod);
	while(M<=n+m) M<<=1;
	for(int i=0;i<=n;i++) read(f[i]);
	for(int i=0;i<=m;i++) read(g[i]);
	MTT(f,g,M,mod);
	for(int i=0;i<=n+m;i++) cout<<f[i]<<" ";
	return 0;
}


