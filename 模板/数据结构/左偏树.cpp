#include<bits/stdc++.h>
#define N 1000005
using namespace std;
int n,m;
int a[N],fa[N],del[N];
int ls[N],rs[N],d[N],rt[N];
int get(int x){
	return x==fa[x]?x:fa[x]=get(fa[x]);
}
int merge(int x,int y){
	if(!x||!y) return x+y;
	if(a[x]>a[y]) swap(x,y);
	rs[x]=merge(rs[x],y);
	if(d[ls[x]]<d[rs[x]]) swap(ls[x],rs[x]);
	d[x]=d[rs[x]]+1;
	return x;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		fa[i]=rt[i]=i;
	}
	scanf("%d",&m);
	while(m--){
		char c=getchar();
		int x,y;
		while(c!='M'&&c!='K') c=getchar();
		scanf("%d",&x);
		if(c=='M'){
			scanf("%d",&y);
			if(del[x]||del[y]) continue;
			x=get(x),y=get(y);
			if(x==y) continue;
			fa[y]=x;
			rt[x]=merge(rt[x],rt[y]);
		}else{
			if(del[x]) {
				puts("0");
				continue;
			}
			x=get(x);
			printf("%d\n",a[rt[x]]);
			del[rt[x]]=1;
			rt[x]=merge(ls[rt[x]],rs[rt[x]]);
		}
	}
	return 0;
}
