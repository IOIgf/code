#include<bits/stdc++.h>
#define N 505
#define ll long long
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	return x*f;
}
int n,m;
ll w[N][N];
ll va[N],vb[N],la[N],lb[N];
ll match[N],upd[N],lst[N];
bool dfs(int x,int fa){
	va[x]=1;
	for(int y=1;y<=n;y++){
		if(vb[y]) continue;
		if(la[x]+lb[y]-w[x][y]==0){
			vb[y]=1;lst[y]=fa;
			if(!match[y]||dfs(match[y],y)){
				match[y]=x;
				return true;
			}
		}
		else if(upd[y]>la[x]+lb[y]-w[x][y])
			upd[y]=la[x]+lb[y]-w[x][y],lst[y]=fa;
	}
	return false;
}
void KM(){
	for(int i=1;i<=n;i++){
		la[i]=-INF;
		for(int j=1;j<=n;j++) la[i]=max(la[i],w[i][j]);
	}
	for(int i=1;i<=n;i++){
		memset(va,0,sizeof(va));
		memset(vb,0,sizeof(vb));
		memset(upd,0x3f,sizeof(upd));
		memset(lst,0,sizeof(lst));
		int st=0;match[0]=i;
		while(match[st]){
			if(dfs(match[st],st)) break;
			ll delta=INF;
			for(int j=1;j<=n;j++)
				if(!vb[j]&&delta>upd[j]) delta=upd[j],st=j;
			for(int j=1;j<=n;j++){
				if(va[j]) la[j]-=delta;
				if(vb[j]) lb[j]+=delta; 
				else upd[j]-=delta;
			}
			vb[st]=1;
		}
		for(;st;st=lst[st]) match[st]=match[lst[st]];
	}
}
int main(){
	n=read(),m=read();
	memset(w,0xc0,sizeof(w));
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		w[x][y]=z;
	}
	KM();
	ll ans=0;
	for(int i=1;i<=n;i++) ans+=w[match[i]][i];
	printf("%lld\n",ans);
	for(int i=1;i<=n;i++) printf("%lld ",match[i]);
	return 0;
}
