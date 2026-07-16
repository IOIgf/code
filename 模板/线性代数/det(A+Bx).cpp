#include<bits/stdc++.h>
#define N 505
#define ll long long
#define mod 998244353
using namespace std;
template<typename T> void read(T &x){
	x=0;int f=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) f=(c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	if(f) x=-x;
}
int n;
ll qmi(ll a,ll b){
	ll ans=1;
	for(;b;b>>=1,a=a*a%mod) if(b&1) ans=ans*a%mod;
	return ans;
}
ll a[N][N],b[N][N];
ll ans=1,cnt;
void B_to_I(){
	for(int i=1;i<=n;i++){
		int p=0;
		for(int j=i;j<=n;j++) if(b[i][j]) p=j;
		while(!p){
			for(int j=1;j<=n;j++) b[i][j]=a[i][j],a[i][j]=0;
			for(int j=1;j<i;j++){
				if(b[i][j]){
					ll rate=b[i][j];
					for(int k=1;k<=n;k++){
						b[i][k]=(b[i][k]-rate*b[j][k]%mod+mod)%mod;
						a[i][k]=(a[i][k]-rate*a[j][k]%mod+mod)%mod;
					}
				}
			}
			for(int j=i;j<=n;j++) if(b[i][j]) p=j;
			if(++cnt==n+1) return;
		}
		if(p!=i){
			ans=mod-ans;
			for(int j=1;j<=n;j++) swap(a[j][i],a[j][p]),swap(b[j][i],b[j][p]);
		}
		ans=ans*b[i][i]%mod;
		ll rate=qmi(b[i][i],mod-2);
		for(int j=1;j<=n;j++) a[i][j]=a[i][j]*rate%mod,b[i][j]=b[i][j]*rate%mod;
		for(int j=1;j<=n;j++){
			if(j==i||!b[j][i]) continue;
			ll rate=b[j][i];
			for(int k=1;k<=n;k++){
				b[j][k]=(b[j][k]-rate*b[i][k]%mod+mod)%mod;
				a[j][k]=(a[j][k]-rate*a[i][k]%mod+mod)%mod;
			}
		}
	}
}
void to_upper_Hessenberg(){
	for(int i=2;i<=n;i++){
		int p=0;
		for(int j=i;j<=n;j++) if(a[j][i-1]) p=j;
		if(!p) continue;
		for(int j=1;j<=n;j++) swap(a[i][j],a[p][j]);
		for(int j=1;j<=n;j++) swap(a[j][i],a[j][p]);
		for(int j=i+1;j<=n;j++){
			if(!a[j][i-1]) continue;
			ll rate=a[j][i-1]*qmi(a[i][i-1],mod-2)%mod;
			for(int k=1;k<=n;k++) a[j][k]=(a[j][k]-a[i][k]*rate%mod+mod)%mod;
			for(int k=1;k<=n;k++) a[k][i]=(a[k][i]+a[k][j]*rate)%mod;
		}
	}
}
ll h[N][N];
void get_eigenpoly(){
	h[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<i;j++){
			h[i][j]=(h[i][j]-h[i-1][j]*a[i][i]%mod+mod)%mod;
			h[i][j+1]=(h[i][j+1]+h[i-1][j])%mod;
		}
		ll mul=a[i][i-1];
		for(int j=i-1;j>=1;j--){
			for(int k=0;k<j;k++)
				h[i][k]=(h[i][k]-h[j-1][k]*mul%mod*a[j][i]%mod+mod)%mod;
			mul=mul*a[j][j-1]%mod;
		}
	}
}
void det_A_plus_Bx(){
	B_to_I();
	if(cnt==n+1){
		for(int i=0;i<=n;i++) cout<<"0 ";
		return;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			a[i][j]=(mod-a[i][j])%mod;
	to_upper_Hessenberg();
	get_eigenpoly();
	for(int i=cnt;i<=n;i++) cout<<ans*h[n][i]%mod<<" ";
	for(int i=1;i<=cnt;i++) cout<<"0 ";
}

int main(){
	read(n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			read(a[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			read(b[i][j]);
	det_A_plus_Bx();
	return 0;
}

