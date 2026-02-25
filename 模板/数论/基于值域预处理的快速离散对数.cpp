#include<bits/stdc++.h>
#define N 2000005
#define ll long long
using namespace std;
template<typename T> void read(T &x){
	x=0;int f=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) f=(c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	if(f) x=-x;
}
int mod,g,q,T,B=2000000;
ll qmi(ll a,ll b){
	ll ans=1;
	for(;b;b>>=1,a=a*a%mod) if(b&1) ans=ans*a%mod;
	return ans;
}
int v[N],p[N],f[N],cp;
int pw[N];
unordered_map<int,int> mp;
int BSGS(int b){
	ll val=qmi(b,mod-2);
	for(int i=0;i<=mod/B+1;i++){
		if(mp.find(val)!=mp.end()&&i*B-mp[val]>=0) return i*B-mp[val];
		val=val*pw[B]%mod;
	}
}
void sieve(int n){
	for(int i=2;i<=n;i++){
		if(!v[i]) {
			v[i]=1,p[++cp]=i;
			f[i]=BSGS(i);
		}
		for(int j=1;j<=cp&&i*p[j]<=n;j++){
			v[i*p[j]]=1;
			f[i*p[j]]=(f[i]+f[p[j]])%(mod-1);
			if(i%p[j]==0) break;
		}
	}
}
ll calc(int x){
	if(x<=T) return f[x];
	int a=mod/x,b=mod%x;
	if(b<=x-b) return ((mod-1)/2+calc(b)-f[a]+(mod-1))%(mod-1);
	return (calc(x-b)-f[a+1]+(mod-1))%(mod-1);
}
int main(){
	read(mod),read(g);
	if(mod<=B){
		ll val=1;
		for(int i=1;i<mod-1;i++){
			val=val*g%mod;
			pw[val]=i;
		}
		read(q);
		while(q--){
			int x;
			read(x);
			cout<<pw[x]<<"\n";
		}
		return 0;
	}
	T=sqrt(mod)+1;
	pw[0]=mp[1]=1;
	for(int i=1;i<=B;i++) {
		pw[i]=(ll)pw[i-1]*g%mod;
		mp[pw[i]]=i;
	}
	sieve(T);
	read(q);
	while(q--){
		int x;
		read(x);
		cout<<calc(x)<<"\n";
	}
	return 0;
}
