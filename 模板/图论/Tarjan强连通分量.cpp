#include<iostream>
#include<vector>
#include<algorithm>
#define N 200005
using namespace std;
int n,m;
int head[N],nxt[N],ver[N],tot;
void add(int x,int y){
	ver[++tot]=y;
	nxt[tot]=head[x];head[x]=tot;
}
int dfn[N],low[N],cd;
int st[N],top,ins[N];
int c[N],vis[N],cnt;
vector<int> scc[N];
void tarjan(int x){
	dfn[x]=low[x]=++cd;
	st[++top]=x;ins[x]=1;
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(ins[y]) low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x]){
		cnt++;int y;
		do{
			y=st[top--];ins[y]=0;
			c[y]=cnt;scc[cnt].push_back(y);
		}while(y!=x);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i]) tarjan(i);
	printf("%d\n",cnt);
	for(int i=1;i<=n;i++){
		if(vis[c[i]]) continue;
		vis[c[i]]=1;
		sort(scc[c[i]].begin(),scc[c[i]].end());
		for(int j=0;j<scc[c[i]].size();j++)
			printf("%d ",scc[c[i]][j]);
		puts("");
	}
	return 0;
}
