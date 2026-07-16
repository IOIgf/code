#include<iostream>
#include<cmath>
#include<algorithm>
#define N 2100005
#define mod 998244353
#define ll long long
using namespace std;
int n,m,k,M;
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
void change(ll *f){
	for(int i=0;i<M;i++){
		rev[i]=rev[i>>1]>>1;
		if(i&1) rev[i]|=M>>1;
		if(i<rev[i]) swap(f[i],f[rev[i]]);
	}
}
void NTT(ll *f,bool flag){
	change(f);
	for(int step=2;step<=M;step<<=1){
		for(int k=0;k<M;k+=step){
			int W=0;
			for(int i=k;i<k+step/2;i++){
				long long a=f[i],b=w[W]*f[i+step/2]%mod;
				f[i]=(a+b)%mod;
				f[i+step/2]=(a-b+mod)%mod;
				W+=M/step;
			}
			
		}
	}
	if(flag){
		reverse(f+1,f+M);
		ll inv=qmi(M,mod-2);
		for(int i=0;i<M;i++) f[i]=f[i]*inv%mod;
	}
}
inline int read(){
	int x=0,f=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	return x*f;
}
int main(){
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	n=read(),m=read();
	while((1<<k)<n+m+1) k++;
	M=1<<k;
	for(int i=0;i<=n;i++) f[i]=read();
	for(int i=0;i<=m;i++) g[i]=read();
	ll W=qmi(3,(mod-1)/M);
	w[0]=1;
	for(int i=1;i<M;i++) w[i]=w[i-1]*W%mod;
	NTT(f,0);
	NTT(g,0);
	for(int i=0;i<M;i++) f[i]=f[i]*g[i]%mod;
	NTT(f,1);
	for(int i=0;i<=n+m;i++) cout<<f[i]<<" ";
	return 0;
}


