#include<iostream>
#include<cstring>
#include<queue>
#define N 200005
using namespace std;
int n,m,s;
int head[N],nxt[N*2],ver[N*2],edge[N*2],tot;
void add(int x,int y,int z){
	ver[++tot]=y;edge[tot]=z;
	nxt[tot]=head[x];head[x]=tot;
}
int d[N],v[N];
queue<int> q;
void spfa(){
	memset(d,0x3f,sizeof(d));
	memset(v,0,sizeof(v));
	d[s]=0;q.push(s);
	while(q.size()){
		int x=q.front();q.pop();v[x]=0;
		for(int i=head[x];i;i=nxt[i]){
			int y=ver[i],z=edge[i];
			if(d[y]>d[x]+z){
				d[y]=d[x]+z;
				if(!v[y]) v[y]=1,q.push(y);
			}
		}
	}
}
int main(){
	scanf("%d%d%d",&n,&m,&s);
	for(int i=1;i<=m;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
	}
	spfa();
	for(int i=1;i<=n;i++) printf("%d ",d[i]); 
	return 0;
}
