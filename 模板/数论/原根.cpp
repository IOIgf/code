#include<iostream>
#define N 1000005
#define ll long long
using namespace std;
int T,n,d;
int v[N],p[N],cp,b[N],phi[N];
void shai(int n){
	phi[1]=1;
	for(int i=2;i<=n;i++){
		if(!v[i]){
			v[i]=i;
			p[++cp]=i;
			phi[i]=i-1;
		}
		for(int j=1;j<=cp;j++){
			if(v[i]<p[j]||i*p[j]>n) break;
			v[i*p[j]]=p[j];
			if(i%p[j]==0) phi[i*p[j]]=phi[i]*p[j];
			else phi[i*p[j]]=phi[i]*(p[j]-1);
		}
	}
	b[2]=b[4]=1;
	for(int j=2;j<=cp;j++)
		for(ll x=p[j];x<=n;x*=p[j]) {
			b[x]=1; 
			if(x*2<=n) b[x*2]=1;
		}
}
ll qmi(ll a,ll b,ll mod){
	ll ans=1;
	for(;b;b>>=1,a=a*a%mod)
		if(b&1) ans=ans*a%mod;
	return ans;
}
ll gcd(ll a,ll b){
	return b?gcd(b,a%b):a;
}
int flag[N];
bool check(int x,int n){
	if(gcd(x,n)!=1) return false;
	int q=phi[n];
	while(q>1){
		int k=v[q];
		while(q%k==0) q/=k;
		if(qmi(x,phi[n]/k,n)==1) return false;
	}
	return true;
}
int main(){
	shai(1000000);
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&d);
		if(!b[n]){
			puts("0"),puts("");
			continue;
		}
		printf("%d\n",phi[phi[n]]);
		int g=1;
		while(g<n&&!check(g,n)) g++;
		for(int i=1;i<=phi[n];i++)
			if(gcd(i,phi[n])==1) flag[qmi(g,i,n)]=1;
		int cnt=0;
		for(int i=1;i<=n;i++){
			if(!flag[i]) continue;
			flag[i]=0;cnt++;
			if(cnt%d==0) printf("%d ",i);
		}
		puts("");
	}
	return 0;
}

/*

10
4 10
999983 100000
999983 100000
999983 100000
999983 100000
999983 100000
999983 100000
999983 100000
999983 100000
999983 100000
999983 100000



*/
