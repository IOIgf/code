#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD=998244353;
int n,a[500005];
int cv[5005],cc[5005],cl;
int nv[5005],nc[5005],nl;
int mv[5005],mc[5005],ml;
int ans;
int hb(int r,int t) {
	for(int h=30;h>=0;h--)
		if(t>= (1ll<<h)&&!((r>>h)&1)) {
			r|=(1ll<<h);
			t-=(1ll<<h);
		}
	return r;
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	cl=0;
	ans=0;
	for(int i=n;i>=1;i--) {
		nl=1;
		nv[0]=a[i];
		nc[0]=1;
		for(int j=0;j<cl;j++) {
			int v=hb(cv[j]|a[i],cv[j]&a[i]);
			nv[nl]=v;
			nc[nl]=cc[j];
			++nl;
		}
		for(int j=0;j<nl;j++){
			for(int k=j+1; k<nl;k++){
				if(nv[j]>nv[k]) {
					swap(nv[j],nv[k]);
					swap(nc[j],nc[k]);
				}
			}
		}	
		ml=0;
		for(int j=0;j<nl;) {
			int v=nv[j],cnt=nc[j];
			int k=j+1;
			while(k<nl&&nv[k]==v){
				cnt=(cnt+nc[k++])%MOD;
			}	
			mv[ml]=v;
			mc[ml]=cnt;
			++ml;
			j=k;
		}
		for(int j=0;j<ml;j++) {
			cv[j]=mv[j];
			cc[j]=mc[j];
		}
		cl=ml;
		for(int j=0;j<cl;j++){
			ans=(ans+cv[j]*cc[j])%MOD;
		}
	}
	cout<<ans%MOD<<'\n';
	return 0;
}
