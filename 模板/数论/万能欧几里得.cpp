#include<bits/stdc++.h>
#define ll long long
#define mod 998244353
#define inv2 499122177
using namespace std;
struct node{
	ll x,y,sy,sy2,sxy;
	node(){x=y=sy=sy2=sxy=0;}
}U,R;
node operator *(node a,node b){
	node c;
	c.x=(a.x+b.x)%mod,c.y=(a.y+b.y)%mod;
	c.sy=(a.sy+b.sy+a.y*b.x)%mod;
	c.sy2=(a.sy2+b.sy2+a.y*a.y%mod*b.x+2*a.y*b.sy)%mod;
	c.sxy=(a.sxy+b.sxy+b.sy*a.x+((b.x+1)*b.x%mod*inv2+a.x*b.x)%mod*a.y)%mod;
	return c;
}
node qmi(node a,ll b){
	node ans=node();
	for(;b;b>>=1,a=a*a) if(b&1) ans=ans*a;
	return ans;
}
node solve(ll a,ll b,ll c,ll n,node U,node R){
	if(!n) return node();
	if(b>=c) return qmi(U,b/c)*solve(a,b%c,c,n,U,R);
	if(a>=c) return solve(a%c,b,c,n,U,qmi(U,a/c)*R);
	ll m=((__int128)a*n+b)/c;
	if(!m) return qmi(R,n);
	return qmi(R,(c-b-1)/a)*U*solve(c,(c-b-1)%a,a,m-1,R,U)*qmi(R,n-((__int128)c*m-b-1)/a);
}
int main(){
	U.y=R.x=1;
	int T;
	scanf("%d",&T);
	while(T--){
		ll n,a,b,c;
		scanf("%lld%lld%lld%lld",&n,&a,&b,&c);
		node ans=solve(a,b,c,n,U,R);
		cout<<(ans.sy+b/c)%mod<<" "<<(ans.sy2+(b/c)*(b/c))%mod<<" "<<ans.sxy<<'\n';
	}
	return 0;
}

