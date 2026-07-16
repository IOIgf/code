#include<bits/stdc++.h>
#define N 605
using namespace std;
template<typename Ty>
void read(Ty &x){
	x=0;int f=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) f=(c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	if(f) x=-x;
}
int n,m;
int a[N][N],del[N],d[N],vis[N];
int contract(int &s,int &t,int cnt){
	for(int i=1;i<=n;i++) d[i]=vis[i]=0;
	for(int i=1,lst=0;i<=cnt;i++){
		int p=0;
		for(int j=1;j<=n;j++) if(!del[j]&&!vis[j]&&d[j]>=d[p]) p=j;
		if(i==cnt) {
			s=lst,t=p;
			return d[p];
		}
		lst=p;vis[p]=1;
		for(int j=1;j<=n;j++) if(!del[j]&&!vis[j]) d[j]+=a[p][j];
	}
}
int Stoer_Wagner(){
	int ans=0x3f3f3f3f;
	for(int i=1;i<n;i++){
		int s,t;
		ans=min(ans,contract(s,t,n-i+1));
		del[t]=1;
		for(int j=1;j<=n;j++){
			if(del[j]||j==s||j==t) continue;
			a[s][j]+=a[t][j],a[j][s]+=a[j][t];
		}
	}
	return ans;
}
int main(){
	read(n),read(m);
	for(int i=1;i<=m;i++){
		int x,y,z;
		read(x),read(y),read(z);
		a[x][y]=a[y][x]=z;
	}
	printf("%d\n",Stoer_Wagner());
	return 0;
}
