#include<iostream>
#define N 20005
using namespace std;
int n,m,s,t;
int head[N],nxt[N],ver[N],edge[N],tot=1;
void add(int x,int y,int z){
	ver[++tot]=y;edge[tot]=z;nxt[tot]=head[x];head[x]=tot;
	ver[++tot]=x;edge[tot]=0;nxt[tot]=head[y];head[y]=tot;
}
int now[N],d[N];
int q[N],l,r;
void bfs(){
	for(int i=1;i<=n;i++) d[i]=-1;
	l=r=1;q[1]=s;d[s]=0;
	while(l<=r){
		int x=q[l++];now[x]=head[x];
		for(int i=head[x];i;i=nxt[i]){
			if(edge[i]==0) continue;
			int y=ver[i];
			if(d[y]==-1) d[y]=d[x]+1,q[++r]=y;
		}
	}
}
long long dinic(int x,long long f){
	if(x==t) return f;
	long long tmp=f;
	for(int i=now[x];i;i=nxt[i]){
		now[x]=i;
		int y=ver[i];
		if(!edge[i]||d[y]!=d[x]+1) continue;
		long long b=dinic(y,min(tmp,(long long)edge[i]));
		if(!b) d[y]=0;
		tmp-=b;
		edge[i]-=b;
		edge[i^1]+=b;
		if(!tmp) break;
	}
	return f-tmp;
}
int main(){
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(int i=1;i<=m;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
	}
	long long ans=0;
	while(1){
		bfs();
		long long f=dinic(s,0x3f3f3f3f3f3f3f3f);
		if(!f) break;
		ans+=f;
	}
	printf("%lld\n",ans);
	return 0;
}
