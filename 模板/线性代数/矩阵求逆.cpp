#include<iostream>
#define mod 1000000007
#define ll long long
using namespace std;
int n;
ll a[405][805];
ll qmi(ll a,ll b){
	ll ans=1;
	for(;b;b>>=1,a=a*a%mod) if(b&1) ans=ans*a%mod;
	return ans;
}
bool gauss(){
	for(int i=1;i<=n;i++){
		int p=0;
		for(int j=i;j<=n;j++) if(a[j][i]) p=j;
		if(!p) return 1;
		for(int j=1;j<=n+n;j++) swap(a[i][j],a[p][j]);
		ll rate=qmi(a[i][i],mod-2);
		for(int j=1;j<=n+n;j++) a[i][j]=a[i][j]*rate%mod;
		for(int j=1;j<=n;j++){
			if(i==j) continue;
			rate=a[j][i];
			for(int k=1;k<=n+n;k++) a[j][k]=(a[j][k]-a[i][k]*rate%mod+mod)%mod;
		}
	}
	return 0;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		a[i][i+n]=1;
		for(int j=1;j<=n;j++) scanf("%d",&a[i][j]);
	}
	if(gauss()) puts("No Solution");
	else{
		for(int i=1;i<=n;i++){
			for(int j=n+1;j<=n+n;j++) printf("%d ",a[i][j]);
			puts("");
		}
	}
	return 0;
} 
