/*
易错：
注意图不连通 
y已遍历时，low[x]=min(low[x],dfn[y])
*/
#include<iostream>
#include<vector>
#define N 4000005
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	return x*f;
}
int n,m;
int head[N],nxt[N],ver[N],tot=1;
void add(int x,int y){
	ver[++tot]=y;
	nxt[tot]=head[x];head[x]=tot;
}
int dfn[N],low[N],cd;
int bri[N],c[N],cnt;
vector<int> dcc[N];
void tarjan(int x,int i0){
	dfn[x]=low[x]=++cd;
	for(int i=head[x];i;i=nxt[i]){
		if(i0==i) continue;
		int y=ver[i];
		if(!dfn[y]){
			tarjan(y,i^1);
			low[x]=min(low[x],low[y]);
			if(dfn[x]<low[y]) bri[i]=bri[i^1]=1;
		}
		else low[x]=min(low[x],dfn[y]);
	}
}
void dfs(int x,int col){
	c[x]=col;dcc[col].push_back(x);
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(bri[i]||c[y]) continue;
		dfs(y,col);
	}
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		add(x,y);add(y,x);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i]) tarjan(i,0);
	for(int i=1;i<=n;i++){
		if(c[i]) continue;
		dfs(i,++cnt);
	}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++){
		printf("%d ",dcc[i].size());
		for(int j=0;j<dcc[i].size();j++)
			printf("%d ",dcc[i][j]);
		puts("");
	}
	return 0;
}
