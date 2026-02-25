#include<bits/stdc++.h>
#define N 1000005
using namespace std;
int n,m,s,t,S,T;
int head[N],nxt[N],ver[N],edge[N],cst[N],tot=1;
void add(int x,int y,int z,int c){
	ver[++tot]=y;edge[tot]=z;cst[tot]=c;nxt[tot]=head[x];head[x]=tot;
	ver[++tot]=x;edge[tot]=0;cst[tot]=-c;nxt[tot]=head[y];head[y]=tot;
}
int d[N],v[N],pre[N];
queue<int> q;
bool spfa(int s,int t,int flag){
	for(int i=0;i<=n+1;i++) d[i]=0x3f3f3f3f;
	d[s]=0;q.push(s);
	while(q.size()){
		int x=q.front();q.pop();v[x]=0;
		for(int i=head[x];i;i=nxt[i]){
			int y=ver[i],z=cst[i];
			if(flag&&(y<1||y>n||i>=tot-1)) continue;
			if(edge[i]&&d[y]>d[x]+z){
				d[y]=d[x]+z;pre[y]=i;
				if(!v[y]) q.push(y),v[y]=1;
			}
		}
	}
	return d[t]!=0x3f3f3f3f;
}
int fl,ans;
void MCMF(int s,int t,int flag){
	while(spfa(s,t,flag)){
		int c=0x3f3f3f3f;
		for(int p=t;p!=s;p=ver[pre[p]^1]) c=min(c,edge[pre[p]]);
		fl+=c;ans+=c*d[t];
		for(int p=t;p!=s;p=ver[pre[p]^1]) edge[pre[p]]-=c,edge[pre[p]^1]+=c;
	}
}
int main(){
	scanf("%d%d%d%d",&n,&m,&s,&t);
	S=0,T=n+1;
	for(int i=1;i<=m;i++){
		int x,y,z,c;
		scanf("%d%d%d%d",&x,&y,&z,&c);
		if(c<0){
			ans+=c*z;
			add(y,x,z,-c);
			add(S,y,z,0);
			add(x,T,z,0);
		}
		else add(x,y,z,c);
	}
	add(t,s,0x3f3f3f3f,0);
	MCMF(S,T,0);
	fl=edge[tot];
	MCMF(s,t,1);
	printf("%d %d\n",fl,ans);
	return 0;
}
