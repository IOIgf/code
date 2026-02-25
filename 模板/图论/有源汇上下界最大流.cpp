#include<bits/stdc++.h>
#define N 1000005
#define INF 0x3f3f3f3f
using namespace std;
int n,m;
int head[N],nxt[N],ver[N],edge[N],tot=1;
void add(int x,int y,int z){
	ver[++tot]=y;edge[tot]=z;nxt[tot]=head[x];head[x]=tot;
	ver[++tot]=x;edge[tot]=0;nxt[tot]=head[y];head[y]=tot;
}
int s,t,s2,t2;
int d[N],q[N],now[N];
bool bfs(int s,int t){
	for(int i=0;i<=t2;i++) d[i]=-1,now[i]=head[i];
	int l=1,r=1;q[1]=s;d[s]=0;
	while(l<=r){
		int x=q[l++];
		for(int i=head[x];i;i=nxt[i]){
			int y=ver[i];
			if(y<=t&&edge[i]&&d[y]==-1) d[y]=d[x]+1,q[++r]=y;
		}
	}
	return d[t]!=-1;
}
int dinic(int x,int t,int f){
	if(x==t) return f;
	int tmp=f;
	for(int i=now[x];i;i=nxt[i]){
		now[x]=i;
		int y=ver[i];
		if(!edge[i]||d[y]!=d[x]+1||y>t) continue;
		int c=dinic(y,t,min(edge[i],tmp));
		if(!c) d[y]=0;
		edge[i]-=c;
		edge[i^1]+=c;
		tmp-=c;
		if(!tmp) break;
	}
	return f-tmp;
}

int main(){
	while(cin>>n>>m){
		s=0,t=n+m+1,s2=n+m+2,t2=n+m+3;
		add(t,s,INF);
		int sum=0;
		for(int i=1;i<=m;i++){
			int x;
			scanf("%d",&x);
			sum+=x;
			add(n+i,t2,x);
			add(s2,t,x);
			add(n+i,t,INF);
		}
		for(int i=1;i<=n;i++){
			int x,y,l,r;
			scanf("%d%d",&x,&y);
			add(s,i,y);
			while(x--){
				scanf("%d%d%d",&y,&l,&r);
				y++;
				sum+=l;
				add(i,t2,l);
				add(s2,n+y,l);
				add(i,n+y,r-l);
			}
		}
		int ans=0;
		while(bfs(s2,t2)) ans+=dinic(s2,t2,INF);
		if(ans!=sum) {
			printf("-1\n\n");
			for(int i=0;i<=n+m+3;i++) head[i]=0;
			tot=1;
			continue;
		}
		ans=edge[3];
		edge[3]=0;
		while(bfs(s,t)) ans+=dinic(s,t,INF);
		printf("%d\n\n",ans);
		for(int i=0;i<=n+m+3;i++) head[i]=0;
		tot=1;
	}
	return 0;
}

/*


先从S'到T'跑一遍最大流
再从S到T跑一遍最大流 
 


*/
