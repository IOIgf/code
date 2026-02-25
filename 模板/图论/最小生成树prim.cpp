/*

易错：
图不连通时，if(!p) 是错的 
if(d[p]==0x3f3f3f3f) 

*/

#include<iostream>
#include<cstring>
#define N 5005
using namespace std;
int n,m,a[N][N];
int d[N],v[N];
int main(){
	scanf("%d%d",&n,&m);
	memset(a,0x3f,sizeof(a));
	memset(d,0x3f,sizeof(d));
	d[1]=0;
	for(int i=1;i<=m;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		a[x][y]=min(a[x][y],z);
		a[y][x]=min(a[y][x],z);
	}
	int cnt=0,ans=0;
	for(int i=1;i<=n;i++){
		int p=0;
		for(int j=1;j<=n;j++)
			if(!v[j]&&(p==0||d[j]<d[p])) p=j;
		if(d[p]==0x3f3f3f3f) break;
		cnt=i;
		ans+=d[p];v[p]=1;
		for(int j=1;j<=n;j++)
			if(!v[j]) d[j]=min(d[j],a[p][j]);
	}
	if(cnt<n) puts("orz");
	else printf("%d\n",ans);
	return 0;
}
