#include<iostream>
#define N 250005
using namespace std;
int n1,n2,m;
int head[N],nxt[N*2],ver[N*2],tot;
void add(int x,int y){
	ver[++tot]=y;
	nxt[tot]=head[x];head[x]=tot;
}
int vis[N],match[N];
bool dfs(int x){
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(!vis[y]){
			vis[y]=1;
			if(!match[y]||dfs(match[y])){
				match[y]=x;
				return true;
			}
		}
	}
	return false;
}
int main(){
	scanf("%d%d%d",&n1,&n2,&m);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y+n1);add(y+n1,x);
	}
	int ans=0;
	for(int i=1;i<=n1;i++){
		for(int j=1;j<=n1+n2;j++) vis[j]=0;
		if(dfs(i)) ans++;
	}
	printf("%d\n",ans);
	return 0;
}
