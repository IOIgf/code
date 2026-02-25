#include<bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define popcnt(x) __builtin_popcountll(x)
using namespace std;
int n,m;
ll E[2][55];
ll ans,anss,ansc;
vector<int> ver[55];
int vis[55],b[55],cnt;

void dfs2(int x){
	vis[x]=1;b[++cnt]=x;
	for(int y:ver[x]) if(!vis[y]) dfs2(y);
}

void dfs(int c,ll now,ll s){
	int deg=0,p=0;
	for(ll t=now;t;t&=t-1){
		int i=__lg(t&-t);
		if(popcnt(E[c][i]&now)>deg){
			deg=popcnt(E[c][i]&now);
			p=i;
		}
	}
	if(deg<=2){
		for(int i=0;i<n;i++) {
			ver[i].clear();vis[i]=0;
			if((now>>i&1)==0) {
				vis[i]=1;
				continue;
			}
			for(ll t=E[c][i]&now;t;t&=t-1) ver[i].push_back(__lg(t&-t));
		}
		ll mul=1;
		for(int i=0;i<n;i++){
			if(vis[i]) continue;
			if(ver[i].size()==0){
				s+=1ll<<i;
				vis[i]=1;
				continue;
			}
			if(ver[i].size()==1){
				cnt=0;
				dfs2(i);
				if((cnt&1)==0) mul=mul*(cnt/2+1);
				for(int j=1;j<=cnt;j+=2) s+=1ll<<b[j];
			}
		}
		for(int i=0;i<n;i++){
			if(vis[i]) continue;
			cnt=0;
			dfs2(i);
			if((cnt&1)==0) mul=mul*2;
			else mul=mul*cnt;
			for(int j=2;j<=cnt;j+=2) s+=1ll<<b[j];
		}
		if(popcnt(s)>ans){
			ans=popcnt(s);
			anss=s;
			ansc=mul;
		}else if(popcnt(s)==ans) ansc+=mul;
		return;
	}
	dfs(c,now-(1ll<<p)-(E[c][p]&now),s+(1ll<<p));
	dfs(c,now-(1ll<<p),s);
}

void solve(int c){
	ans=anss=ansc=0;
	dfs(c,(1ll<<n)-1,0);
	cout<<ans<<" "<<ansc<<"\n";
	for(int i=0;i<n;i++) if(anss>>i&1) cout<<i+1<<" ";
	cout<<"\n";
}
int main(){
	freopen("P12371_24.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		E[1][x-1]|=1ll<<y-1;
		E[1][y-1]|=1ll<<x-1;
	}
	for(int i=0;i<n;i++) E[0][i]=(1ll<<n)-1-(1ll<<i)-E[1][i];
	solve(0);
	solve(1);
	return 0;
}

