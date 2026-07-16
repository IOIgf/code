#include<bits/stdc++.h>
#define N 50005
#define ll long long
#define fi first
#define se second
using namespace std;
template<typename T> void read(T &x){
	x=0;int f=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) f=(c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	if(f) x=-x;
}
int n,q,m;
int a[N];
pair<int,int> d[N];
vector<pair<int,int>> qs[N*4];
int ans[N*4];
vector<int> v[2][230];
void insert(int c,int k,int r){
	if(r==m+1) return;
	int pos=lower_bound(v[c][r].begin(),v[c][r].end(),k)-v[c][r].begin();
	if(pos==v[c][r].size()) v[c][r].push_back(k);
	else{
		insert(c,v[c][r][pos],r+1);
		v[c][r][pos]=k;
	}
}
int main(){
	read(n),read(q);
	for(int i=1;i<=n;i++) read(d[i].fi),d[i].se=n-i+1;
	sort(d+1,d+n+1);
	for(int i=1;i<=n;i++) a[n-d[i].se+1]=i;
	for(int i=1;i<=q;i++){
		int x,k;
		read(x),read(k);
		qs[x].push_back({k,i});
	}
	m=sqrt(n)+1;
	for(int i=1;i<=n;i++){
		insert(0,a[i],1);
		insert(1,-a[i],1);
		for(auto st:qs[i]){
			int k=st.fi,num=st.se;
			for(int j=1;j<=min(k,m);j++) ans[num]+=v[1][j].size();
			if(k>m){
				for(int j=1;j<=m;j++) if(v[0][j].size()>m) ans[num]+=min(k,(int)v[0][j].size())-m;
			}
		}
	}
	for(int i=1;i<=q;i++) cout<<ans[i]<<"\n";
	return 0;
}



