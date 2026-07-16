#include<iostream>
#include<cstring>
#define mod 1000003
#define ll long long
using namespace std;
int n,T;
ll qmi(ll a,ll b){
	ll ans=1;
	for(;b;b>>=1,a=a*a%mod) if(b&1) ans=ans*a%mod;
	return ans;
}
ll a1[105][105];
ll a[105][105],deg[105],ind[105],fac[4000005];
ll gauss(){
	ll ans=1;
	for(int i=1;i<n;i++){
		int p=0;
		for(int j=i;j<n;j++) if(a[j][i]) p=j;
		if(!p) return 0;
		if(p!=i) ans*=-1;
		for(int j=1;j<n;j++) swap(a[i][j],a[p][j]);
		for(int j=i+1;j<n;j++){
			ll rate=a[j][i]*qmi(a[i][i],mod-2);
			for(int k=1;k<n;k++) a[j][k]=(a[j][k]-rate*a[i][k])%mod;
		}
	}
	for(int i=1;i<n;i++) ans=ans*a[i][i]%mod;
	return (ans+mod)%mod;
}
int fa[105];
int get(int x){
	return x==fa[x]?x:fa[x]=get(fa[x]);
}
int d[105],pos[105];
int main(){
	fac[0]=1;
	for(int i=1;i<=4000000;i++) fac[i]=fac[i-1]*i%mod;
	scanf("%d",&T);
	while(T--){
		memset(a1,0,sizeof(a1));
		memset(a,0,sizeof(a));
		memset(deg,0,sizeof(deg));
		memset(ind,0,sizeof(ind));
		scanf("%d",&n);
		int cnt=0,dt=0;
		for(int i=1;i<=n;i++){
			scanf("%lld",&deg[i]);
			cnt+=deg[i];fa[i]=i;
			for(int j=1;j<=deg[i];j++){
				int x;
				scanf("%d",&x);
				a1[i][x]++;
				ind[x]++;
			}
		}
		if(n==1||cnt==0){
			puts("1");
			continue;
		}
		int flag=0;
		for(int i=1;i<=n;i++) {
			if(deg[i]!=ind[i]) flag=1;
			if(deg[i]) {
				d[++dt]=i;
				pos[i]=dt;
			}
		}
		if(flag||!deg[1]){
			puts("0");
			continue;
		}
		for(int i=1;i<=n;i++){
			if(deg[i]==0) continue;
			a[pos[i]][pos[i]]=deg[i];
			for(int j=1;j<=n;j++) a[pos[i]][pos[j]]-=a1[i][j];
		}
		n=dt;
		cnt=n;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(a[i][j]){
					int x=get(i),y=get(j);
					if(x!=y) cnt--,fa[x]=y;
				}
			}
		}
		if(cnt!=1){
			puts("0");
			continue;
		}
		ll ans=gauss();
		for(int i=1;i<=n;i++) ans=ans*fac[deg[d[i]]-1]%mod;
		printf("%lld\n",ans*deg[1]%mod);
	}
	return 0;
}

/*

1
2
2 2 1
1 1


1
3
2 2 3
2 1 3
2 1 2

*/
