#include<iostream>
#include<cstring>
#define mod 998244353
#define N 200005
#define ll long long
#define inv2 499122177
using namespace std;
int n,m;
ll a[N],b[N];
ll f[N],g[N];
void FMT(ll *f,int l,int r,int flag,int op){
	if(l==r) return;
	int mid=(l+r)/2,len=(r-l+1)/2;
	FMT(f,l,mid,flag,op);
	FMT(f,mid+1,r,flag,op);
	if(op==1){
		for(int i=mid+1;i<=r;i++) 
			f[i]=(f[i]+f[i-len]*flag+mod)%mod;
	}
	if(op==2){
		for(int i=l;i<=mid;i++) 
			f[i]=(f[i]+f[i+len]*flag+mod)%mod;
	}
	if(op==3){
		for(int i=l;i<=mid;i++) {
			ll a=f[i],b=f[i+len];
			f[i]=(a+b)%mod;
			f[i+len]=(a-b+mod)%mod;
			if(flag==-1) {
				f[i]=f[i]*inv2%mod;
				f[i+len]=f[i+len]*inv2%mod;
			}
		}
	}
}
void solve(int op){
	memcpy(f,a,sizeof(f));
	memcpy(g,b,sizeof(g));
	FMT(f,0,m-1,1,op);
	FMT(g,0,m-1,1,op);
	for(int i=0;i<m;i++) f[i]=f[i]*g[i]%mod;
	FMT(f,0,m-1,-1,op);
	for(int i=0;i<m;i++) printf("%lld ",f[i]);
	puts("");
}
int main(){
	scanf("%d",&n);
	m=1<<n;
	for(int i=0;i<m;i++) scanf("%d",&a[i]);
	for(int i=0;i<m;i++) scanf("%d",&b[i]);
	solve(1);
	solve(2);
	solve(3);
	return 0;
}
