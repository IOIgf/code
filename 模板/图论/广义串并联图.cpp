#include<bits/stdc++.h>
#define N 400005
#define ll long long
#define mod 998244353
using namespace std;
template<typename T> void read(T &x){
	x=0;int f=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) f=(c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	if(f) x=-x;
}
int n,m;
map<pair<int,int>,int> mp;
int deg[N],ax[N],ay[N],del[N];
vector<int> v[N];
ll f[N],g[N];

int main(){
	read(n),read(m);
	for(int i=1;i<=m;i++){
		int x,y;
		read(x),read(y);
		if(mp[{x,y}]){
			f[mp[{x,y}]]++;
			continue;
		}
		ax[i]=x,ay[i]=y;
		mp[{x,y}]=mp[{y,x}]=i;
		v[x].push_back(i);
		v[y].push_back(i);
		deg[x]++,deg[y]++;
		f[i]=g[i]=1;
	}
	queue<int> q;
	for(int i=1;i<=n;i++) if(deg[i]<=2) q.push(i);
	ll ans=1;
	while(q.size()){
		int x=q.front();q.pop();
		del[x]=1;
		if(deg[x]==0) continue;
		if(deg[x]==1){
			int ed=0;
			for(int i:v[x]) if(!del[ax[i]^ay[i]^x]) ed=i;
			ans=ans*f[ed]%mod;
			int y=ax[ed]^ay[ed]^x;
			if(--deg[y]==2) q.push(y);
			continue;
		}
		int ed1=0,ed2=0;
		for(int i:v[x])
			if(!del[ax[i]^ay[i]^x]) {
				if(!ed1) ed1=i;
				else ed2=i;
			}
		ll f2=f[ed1]*f[ed2]%mod,g2=(g[ed1]*f[ed2]+g[ed2]*f[ed1])%mod;
		int y1=ax[ed1]^ay[ed1]^x,y2=ax[ed2]^ay[ed2]^x;
		if(mp[{y1,y2}]){
			int ed3=mp[{y1,y2}];
			ll f3=(f2*g[ed3]+f[ed3]*g2)%mod,g3=g2*g[ed3]%mod;
			f[ed3]=f3,g[ed3]=g3;
			if(--deg[y1]==2) q.push(y1);
			if(--deg[y2]==2) q.push(y2);
		}else{
			mp[{y1,y2}]=mp[{y2,y1}]=++m;
			f[m]=f2,g[m]=g2;
			ax[m]=y1,ay[m]=y2;
			v[y1].push_back(m);
			v[y2].push_back(m);
		}
	}
	cout<<ans; 
	return 0;
}


