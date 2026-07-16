#include<bits/stdc++.h>
#define mod 998244353
#define ll long long
#define N 100005
using namespace std;
template<typename T> void read(T &x){
	x=0;int f=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) f=(c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	if(f) x=-x;
}
int n,k,M=65536;
ll qmi(ll a,ll b){
	ll ans=1;
	for(;b;b>>=1,a=a*a%mod) if(b&1) ans=ans*a%mod;
	return ans;
}
ll f[N],g[N],g2[N];
int rev[N];
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

ll Bostan_Mori(ll *f,ll *g,int n,int M){
	if(n==0) return f[0]*qmi(g[0],mod-2)%mod;
	for(int i=0;i<M;i++){
		if(i&1) g2[i]=g[i];
		else g2[i]=(mod-g[i])%mod;
	}
	polymul(f,g2,M);
	NTT(g,0,M);
	for(int i=0;i<M;i++) g[i]=g[i]*g2[i]%mod;
	NTT(g,1,M);
	for(int i=0;i<M;i+=2) g[i/2]=g[i];
	for(int i=n&1;i<M;i+=2) f[i/2]=f[i];
	for(int i=M/2;i<M;i++) f[i]=g[i]=0;
	return Bostan_Mori(f,g,n/2,M);
}

int main(){
	read(n),read(k);
	for(int i=1;i<=k;i++) read(g[i]);
	g[0]=-1;
	for(int i=0;i<k;i++) read(f[i]);
	polymul(f,g,M);
	NTT(g,1,M);
	for(int i=k;i<M;i++) f[i]=0;
	cout<<Bostan_Mori(f,g,n,M);
	return 0;
}




