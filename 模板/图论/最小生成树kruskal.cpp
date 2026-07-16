#include<iostream>
#include<algorithm>
#define N 200005
using namespace std;
int n,m;
struct edges{
	int x,y,z;
}a[N];
bool cmp(edges a,edges b){
	return a.z<b.z;
}
int fa[N];
int get(int x){
	return x==fa[x]?x:fa[x]=get(fa[x]);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z);
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=n;i++) fa[i]=i;
	int cnt=n,ans=0;
	for(int i=1;i<=m;i++){
		int x=get(a[i].x),y=get(a[i].y);
		if(x==y) continue;
		fa[x]=y,cnt--;ans+=a[i].z;
	}
	if(cnt>1) puts("orz");
	else printf("%d\n",ans);
	return 0;
} 
