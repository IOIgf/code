#include<bits/stdc++.h>
#define N 605
#define ll long long
using namespace std;
template<typename T> void read(T &x){
	x=0;int f=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) f=(c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	if(f) x=-x;
}
int n,mod;
ll qmi(ll a,ll b){
	ll ans=1;
	for(;b;b>>=1,a=a*a%mod) if(b&1) ans=ans*a%mod;
	return ans;
}
ll a[N][N];
ll det(){
	ll ans=1;
	for(int i=1;i<=n;i++){
		int p=0;
		for(int j=i;j<=n;j++) if(a[j][i]) p=j;
		if(!p) return 0;
		if(p!=i){
			ans=mod-ans;
			for(int j=1;j<=n;j++) swap(a[i][j],a[p][j]);
		}
		for(int j=i+1;j<=n;j++){
			while(a[j][i]){
				ll rate=a[j][i]/a[i][i];
				for(int k=1;k<=n;k++) {
					a[j][k]-=a[i][k]*rate%mod;
					if(a[j][k]<0) a[j][k]+=mod;
				}
				if(!a[j][i]) break;
				ans=mod-ans;
				for(int k=1;k<=n;k++) swap(a[j][k],a[i][k]);
			}
		}
	}
	for(int i=1;i<=n;i++) ans=ans*a[i][i]%mod;
	return ans;
}
int main(){
	read(n),read(mod);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			read(a[i][j]);
			a[i][j]%=mod;
		}
	cout<<det();
	return 0;
}

