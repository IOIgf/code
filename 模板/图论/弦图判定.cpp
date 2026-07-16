#include<bits/stdc++.h>
#define N 10005
using namespace std;
int n,m;
vector<int> v[N];
int label[N],rk[N],p[N];
int head[N],nxt[N],pre[N];
void MCS(){
	for(int i=1;i<=n;i++)
		nxt[i]=head[0],pre[head[0]]=i,head[0]=i;
	int val=0;
	for(int i=n;i>=1;i--){
		int x=head[val];
		p[i]=x,rk[x]=i;
		pre[nxt[x]]=0;head[val]=nxt[x];
		for(int y:v[x]){
			if(rk[y]) continue;
			nxt[pre[y]]=nxt[y],pre[nxt[y]]=pre[y];
			if(y==head[label[y]]) head[label[y]]=nxt[y];
			label[y]++;
			pre[y]=nxt[y]=0;
			nxt[y]=head[label[y]],pre[head[label[y]]]=y,head[label[y]]=y;
		}
		if(head[val+1]) val++;
		while(val&&!head[val]) val--;
	}
}
bool connect(int x,int y){
	int d=lower_bound(v[x].begin(),v[x].end(),y)-v[x].begin();
	return d<v[x].size()&&v[x][d]==y;
}
bool check(){
	for(int i=1;i<=n;i++){
		int v1=0;
		for(int y:v[p[i]]){
			if(rk[y]<i) continue;
			if(!v1||rk[y]<rk[v1]) v1=y;
		}
		for(int y:v[p[i]]){
			if(rk[y]<i||y==v1) continue;
			if(!connect(v1,y)) return 0;
		}
	}
	return 1;
}
int main(){
	while(cin>>n>>m,n){
		for(int i=1;i<=m;i++){
			int x,y;
			scanf("%d%d",&x,&y);
			v[x].push_back(y);
			v[y].push_back(x);
		}
		for(int i=1;i<=n;i++) sort(v[i].begin(),v[i].end());
		MCS();
		if(check()) puts("Perfect");
		else puts("Imperfect");
		for(int i=1;i<=n;i++) {
			v[i].clear();
			rk[i]=p[i]=label[i]=0;
			head[i]=nxt[i]=pre[i]=0;
		}
	}
}

