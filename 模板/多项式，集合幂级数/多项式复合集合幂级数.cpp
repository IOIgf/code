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
ll a[1<<20][21],b[1<<20][21];
void change(ll *f,ll a[1<<20][21],int n){
	for(int i=0;i<(1<<n);i++){
		for(int j=0;j<=n;j++) a[i][j]=0;
		a[i][cnt[i]]=f[i];
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<(1<<n);j++)
			if(j&(1<<i))
				for(int k=0;k<=n;k++) a[j][k]+=a[j-(1<<i)][k];
	for(int i=0;i<(1<<n);i++)
		for(int j=0;j<=n;j++) a[i][j]%=mod;
}

void convol(int n){
	for(int i=0;i<(1<<n);i++){
		for(int j=n;j>=0;j--){
			ll val=0;
			for(int k=0;k<=(j>>1);k++) val+=a[i][k]*b[i][j-k];
			val%=mod;
			for(int k=(j>>1)+1;k<=j;k++) val+=a[i][k]*b[i][j-k];
			a[i][j]=val%mod;
		}
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<(1<<n);j++)
			if(j&(1<<i))
				for(int k=0;k<=n;k++) a[j][k]-=a[j-(1<<i)][k];
}
ll f[1<<20],f2[1<<20];
ll h[21][1<<20];
int main(){
	read(n);
	for(int i=0;i<(1<<n-1);i++) cnt[i*2]=cnt[i],cnt[i*2+1]=cnt[i]+1;
	for(int i=0;i<(1<<n);i++) read(f[i]);
	ll fac=1;
	for(int i=0;i<=n;i++) {
		ll x=0;
		read(x);
		h[i][0]=fac*x%mod;
		fac=fac*(i+1)%mod;
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<(1<<i-1);j++){
			f2[j]=0;
			f2[j+(1<<i-1)]=f[j+(1<<i-1)];
		}
		change(f2,b,i);
		for(int j=0;j<=n-i;j++){
			change(h[j+1],a,i);
			convol(i);
			for(int k=0;k<(1<<i);k++) h[j][k]=(h[j][k]+a[k][cnt[k]]%mod+mod)%mod;
		}
	}
	for(int i=0;i<(1<<n);i++) cout<<h[0][i]<<" ";
	return 0;
}


