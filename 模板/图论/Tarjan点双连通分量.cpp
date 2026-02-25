#include<iostream>
#include<vector>
#define N 4000005
using namespace std;
int n,m;
inline int read(){
	int x=0,f=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	return x*f;
}
int head[N],nxt[N],ver[N],tot;
void add(int x,int y){
	ver[++tot]=y;
	nxt[tot]=head[x];head[x]=tot;
} 
int dfn[N],low[N],cd;
int st[N],top,cnt;
vector<int> dcc[N];
void tarjan(int x){
	dfn[x]=low[x]=++cd;
	st[++top]=x;
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
			if(dfn[x]<=low[y]){
				cnt++;int z;
				do{
					z=st[top--];
					dcc[cnt].push_back(z);
				}while(z!=y);
				dcc[cnt].push_back(x);
			}
		}
		else low[x]=min(low[x],dfn[y]);
	}
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		add(x,y);add(y,x);
	}
	for(int x=1;x<=n;x++){
		if(!dfn[x]) {
			tarjan(x);
			int f=0;
			for(int i=head[x];i;i=nxt[i])
				if(ver[i]!=x) f=1;
			if(!f) dcc[++cnt].push_back(x);
			top=0;
		}
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

