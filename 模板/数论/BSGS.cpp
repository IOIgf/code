#include<iostream>
#include<cmath>
#include<map>
#define ll long long
using namespace std;
ll p,a,b;
ll BSGS(ll a,ll b,ll p){
	map<ll,ll> m;
	ll t=sqrt(p)+1,x=b,x2=1;
	for(int i=0;i<=t;i++){
		m[x]=i;
		x=x*a%p;
	}
	x=1;
	for(int i=1;i<=t;i++) x=x*a%p;
	for(int i=0;i<=t;i++){
		if(m.find(x2)!=m.end())
			if(i*t-m[x2]>=0) return i*t-m[x2];
		x2=x2*x%p;
	}
	return -1;
}
int main(){
	scanf("%d%d%d",&p,&a,&b);
	ll ans=BSGS(a,b,p);
	if(ans==-1) puts("no solution");
	else printf("%d\n",ans);
	return 0;
}

/*

998244353
10231
451561



*/
