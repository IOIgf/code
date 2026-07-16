#include<iostream>
#include<cmath>
#include<algorithm>
#define N 2100005
#define mod 998244353
#define ll long long
using namespace std;
int n,m,k;
ll qmi(ll a,ll b){
	ll ans=1;
	for(;b;b>>=1){
		if(b&1) ans=ans*a%mod;
		a=a*a%mod;
	}
	return ans;
}
ll f[N],g[N],w[N];
int rev[N];
void change(ll *f,int M){
	for(int i=0;i<M;i++){
		rev[i]=rev[i>>1]>>1;
		if(i&1) rev[i]|=M>>1;
		if(i<rev[i]) swap(f[i],f[rev[i]]);
	}
}
void NTT(ll *f,bool flag,int M){
	change(f,M);
	for(int step=2;step<=M;step<<=1){
		ll wn=qmi(3,(mod-1)/step);
		for(int k=0;k<M;k+=step){
			ll w=1;
			for(int i=k;i<k+step/2;i++){
				long long a=f[i],b=w*f[i+step/2]%mod;
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
void calc(ll *f,ll *g,int M){
	NTT(f,0,M);
	NTT(g,0,M);
	for(int i=0;i<M;i++) f[i]=f[i]*g[i]%mod;
	NTT(f,1,M);
}
ll a[N],b[N];
void cdq(int l,int r){
	if(l==r) return;
	int mid=(l+r)/2;
	cdq(l,mid);
	int len=r-l+1;
	for(int i=0;i<len*2;i++) a[i]=b[i]=0;
	for(int i=1;i<len;i++) a[i]=g[i];
	for(int i=0;i<len/2;i++) b[i]=f[l+i];
	calc(a,b,len*2);
	for(int i=1;i<=len/2;i++) f[mid+i]=(f[mid+i]+a[i+len/2-1])%mod;
	cdq(mid+1,r);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++) scanf("%lld",&g[i]);
	while((1<<k)<n) k++;
	f[0]=1;
	cdq(0,(1<<k)-1);
	for(int i=0;i<n;i++) printf("%lld ",f[i]);
	return 0;
}


