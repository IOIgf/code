#include<bits/stdc++.h>
#define N 5005
#define ll unsigned long long
using namespace std;
template<typename T> void read(T &x){
	x=0;int f=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) f=(c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	if(f) x=-x;
}
ll tab[256][256];
ll mul(ll x,ll y,int p=64){
	if(x<=1||y<=1) return x*y;
	if(p<8&&tab[x][y]) return tab[x][y];p>>=1;
	ll a=x>>p,b=((1ull<<p)-1)&x,c=y>>p,d=((1ull<<p)-1)&y;
	ll ac=mul(a,c,p),bd=mul(b,d,p),q=mul(a^b,c^d,p);
	ll ans=mul(ac,1ull<<p-1,p)^bd^((bd^q)<<p);
	if(p<8) tab[x][y]=tab[y][x]=ans;
	return ans;
}

ll qmi(ll a,ll b){
	ll ans=1;
	for(;b;b>>=1,a=mul(a,a)) if(b&1) ans=mul(ans,a);
	return ans;
}

bool flag;

ll BSGS(ll a,ll b,ll p){
	if(b==1) return 0;
	map<ll,int> mp;int t=sqrt(p)+1;
	ll x=1;
	for(int i=0;i<t;i++){
		mp[mul(b,x)]=i;
		x=mul(x,a);
	}
	a=x;x=1;
	for(int i=0;i<=t;i++){
		if(mp.find(x)!=mp.end()&&i*t-mp[x]>=0) return i*t-mp[x];
		x=mul(x,a);
	}
	flag=0;
	return 0;
}
const ll p[7]={3,5,17,257,641,65537,6700417},P=-1;


ll calc(int k,ll a,ll b){
	if(k==7){
		if(b!=1) flag=0;
		return 0;
	}
	ll t=BSGS(qmi(a,P/p[k]),qmi(b,P/p[k]),p[k]);
	if(!flag) return 0;
	ll s=calc(k+1,qmi(a,p[k]),mul(qmi(a,P-t),b));
	if(!flag) return 0;
	return s*p[k]+t;
}


int main(){
	int T;
	read(T);
	while(T--){
		ll a,b;
		read(a),read(b);
		flag=1;
		ll ans=calc(0,a,b);
		if(!flag) cout<<"-1\n";
		else cout<<ans<<"\n";
	}
	return 0;
}


