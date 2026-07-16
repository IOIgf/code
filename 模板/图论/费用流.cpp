#include<iostream>
#include<queue>
#define N 30005
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
int n,m;
int head[N],nxt[N],ver[N],edge[N],cst[N],tot=1;
void add(int x,int y,int z,int c){
	ver[++tot]=y;edge[tot]=z;cst[tot]=c;
	nxt[tot]=head[x];head[x]=tot;
	ver[++tot]=x;edge[tot]=0;cst[tot]=-c;
	nxt[tot]=head[y];head[y]=tot;
}
long long d[N];
int v[N],pre[N];
queue<int> q;
void spfa(){
	for(int i=1;i<=n;i++){
		d[i]=INF;
		v[i]=pre[i]=0;
	}
	q.push(1);d[1]=0;
	while(q.size()){
		int x=q.front();q.pop();
		v[x]=0;
		for(int i=head[x];i;i=nxt[i]){
			int y=ver[i];
			if(edge[i]==0) continue;
			if(d[y]>d[x]+cst[i]){
				d[y]=d[x]+cst[i];
				pre[y]=i;
				if(!v[y]) q.push(y),v[y]=1;
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	while(m--){
		int x,y,z,c;
		scanf("%d%d%d%d",&x,&y,&z,&c);
		add(x,y,z,c);
	}
	long long mxf=0,ans=0;
	while(1){
		spfa();
		if(d[n]==INF) break;
		int f=0x3f3f3f3f;
		for(int p=n;p!=1;p=ver[pre[p]^1]) f=min(f,edge[pre[p]]);
		mxf+=f;
		ans+=d[n]*f;
		for(int p=n;p!=1;p=ver[pre[p]^1]) {
			edge[pre[p]]-=f;
			edge[pre[p]^1]+=f;
		}
	}
	printf("%lld %lld\n",mxf,ans);
	return 0;
} 
