#include<iostream>
#include<cstring>
#include<map>
#define N 5000005
#define ll long long
using namespace std;
int m=5000000;
int v[N],p[N],cp;
ll phi[N],mu[N];
void shai(){
	phi[1]=mu[1]=1;
	for(int i=2;i<=m;i++){
		if(!v[i]){
			v[i]=p[++cp]=i;
			phi[i]=i-1,mu[i]=-1;
		}
		for(int j=1;j<=cp;j++){
			if(v[i]<p[j]||i*p[j]>m) break;
			v[i*p[j]]=p[j];
			if(i%p[j]==0){
				mu[i*p[j]]=0;
				phi[i*p[j]]=phi[i]*p[j];
			}else{
				mu[i*p[j]]=-mu[i];
				phi[i*p[j]]=phi[i]*(p[j]-1);
			}
		}
	}
	for(int i=1;i<=m;i++){
		phi[i]+=phi[i-1];
		mu[i]+=mu[i-1];
	}
}
ll f1[10005],f2[10005],n1;
ll du1(ll n){
	if(n<=m) return phi[n];
	if(f1[n1/n]) return f1[n1/n];
	ll h=n*(n+1)/2;
	for(ll l=2,r;l<=n;l=r+1){
		r=n/(n/l);
		h-=(r-l+1)*du1(n/l);
	}
	return f1[n1/n]=h;
}
ll du2(ll n){
	if(n<=m) return mu[n];
	if(f2[n1/n]) return f2[n1/n];
	ll h=1;
	for(ll l=2,r;l<=n;l=r+1){
		r=n/(n/l);
		h-=(r-l+1)*du2(n/l);
	}
	return f2[n1/n]=h;
}
int main(){
	shai();
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%lld",&n1);
		memset(f1,0,sizeof(f1));
		memset(f2,0,sizeof(f2));
		printf("%lld %lld\n",du1(n1),du2(n1));
	}
}

/*


10
1000000000
2000000000
1500000000
2147483647
1234567890
1000000000
2000000000
1500000000
2147483647
1234567890


*/
