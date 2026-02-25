#include<bits/stdc++.h>
#define ll long long
#define mod 998244353
using namespace std;
template<typename T> void read(T &x){
	x=0;int f=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) f=(c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	if(f) x=-x;
}
int n,cnt[1<<20];
ll qmi(ll a,ll b){
	ll ans=1;
	for(;b;b>>=1,a=a*a%mod) if(b&1) ans=ans*a%mod;
	return ans;
}
ll f[1<<20];
ll a[1<<20][21],a2[1<<20][21],b[21],inv[21];
void FMT(ll a[1<<20][21]){
	for(int i=0;i<n;i++)
		for(int j=0;j<(1<<n);j++)
			if(j&(1<<i)) 
				for(int k=0;k<=n;k++) a[j][k]+=a[j-(1<<i)][k];
	for(int i=0;i<(1<<n);i++)
		for(int j=0;j<=n;j++) a[i][j]%=mod;
}
void IFMT(ll a[1<<20][21]){
	for(int i=0;i<n;i++)
		for(int j=0;j<(1<<n);j++)
			if(j&(1<<i)) 
				for(int k=0;k<=n;k++) a[j][k]-=a[j-(1<<i)][k];
	for(int i=0;i<(1<<n);i++)
		for(int j=0;j<=n;j++) a[i][j]=(a[i][j]%mod+mod)%mod;
}
void change1(ll *f,ll a[1<<20][21]){
	for(int i=0;i<(1<<n);i++)
		for(int j=0;j<=n;j++) a[i][j]=0;
	for(int i=0;i<(1<<n);i++) a[i][cnt[i]]=f[i];
	FMT(a);
}
void change2(ll *f,ll a[1<<20][21]){
	IFMT(a);
	for(int i=0;i<(1<<n);i++) f[i]=a[i][cnt[i]];
}
void Inv(ll *f){
	for(int i=0;i<(1<<(n-1));i++) cnt[i*2]=cnt[i],cnt[i*2+1]=cnt[i]+1;
	change1(f,a);
	ll inv=qmi(a[0][0],mod-2);
	for(int i=0;i<(1<<n);i++){
		b[0]=inv;
		for(int j=1;j<=n;j++){
			b[j]=0;
			for(int k=1;k<=j;k++) b[j]-=b[j-k]*a[i][k]%mod;
			b[j]=(b[j]%mod+mod)*inv%mod;
		}
		for(int j=0;j<=n;j++) a[i][j]=b[j];
	}
	change2(f,a);
}
void Ln(ll *f){
	for(int i=0;i<(1<<(n-1));i++) cnt[i*2]=cnt[i],cnt[i*2+1]=cnt[i]+1;
	for(int i=0;i<=n;i++) inv[i]=qmi(i,mod-2);
	change1(f,a);
	for(int i=0;i<(1<<n);i++){
		memset(b,0,sizeof(b));
		for(int j=1;j<=n;j++){
			for(int k=1;k<j;k++) b[j]+=b[k]*a[i][j-k]%mod;
			b[j]=(j*a[i][j]-b[j]%mod+mod)%mod;
		}
		for(int j=0;j<=n;j++) a[i][j]=b[j]*inv[j]%mod;
	}
	change2(f,a);
}
void Exp(ll *f){
	for(int i=0;i<(1<<(n-1));i++) cnt[i*2]=cnt[i],cnt[i*2+1]=cnt[i]+1;
	for(int i=0;i<=n;i++) inv[i]=qmi(i,mod-2);
	change1(f,a);
	for(int i=0;i<(1<<n);i++){
		memset(b,0,sizeof(b));
		b[0]=1;
		for(int j=1;j<=n;j++) a[i][j]=a[i][j]*j%mod;
		for(int j=1;j<=n;j++){
			for(int k=1;k<=j;k++) b[j]+=a[i][k]*b[j-k]%mod;
			b[j]=b[j]%mod*inv[j]%mod;
		}
		for(int j=0;j<=n;j++) a[i][j]=b[j];
	}
	change2(f,a);
}
void Mul(ll *f,ll *g){
	for(int i=0;i<(1<<(n-1));i++) cnt[i*2]=cnt[i],cnt[i*2+1]=cnt[i]+1;
	change1(f,a);
	change1(g,a2);
	for(int i=0;i<(1<<n);i++){
		memset(b,0,sizeof(b));
		for(int j=0;j<=n;j++)
			for(int k=0;k<=j;k++) b[j]+=a[i][k]*a2[i][j-k]%mod;
		for(int j=0;j<=n;j++) a[i][j]=b[j]%mod;
	}
	change2(f,a);
}
int main(){
	read(n);
	for(int i=0;i<(1<<n);i++) read(f[i]);
	Exp(f);
	for(int i=0;i<(1<<n);i++) cout<<f[i]<<" ";
	return 0;
}

