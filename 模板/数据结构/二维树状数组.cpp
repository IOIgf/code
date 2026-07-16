#include<iostream>
#define N 2050
using namespace std;
int n,m;
char op;
long long c[4][N][N];
void add1(int f,int x,int y,int k){
	for(;x<N;x+=x&-x)
		for(int t=y;t<N;t+=t&-t) c[f][x][t]+=k;
}
long long ask1(int f,int x,int y){
	long long ans=0;
	for(;x;x-=x&-x)
		for(int t=y;t;t-=t&-t)  ans+=c[f][x][t];
	return ans;
}
void add2(int x,int y,int k){
	add1(0,x,y,k);
	add1(1,x,y,k*x);
	add1(2,x,y,k*y);
	add1(3,x,y,k*x*y);
}
long long ask2(int x,int y){
	return ask1(0,x,y)*(x+1)*(y+1)-ask1(1,x,y)*(y+1)-ask1(2,x,y)*(x+1)+ask1(3,x,y);
}
int main(){
	cin>>op>>n>>m;
	while(cin>>op){
		int x1,x2,y1,y2,z;
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		if(op=='L'){
			scanf("%d",&z);
			add2(x1,y1,z);
			add2(x1,y2+1,-z);
			add2(x2+1,y1,-z);
			add2(x2+1,y2+1,z);
		}
		else printf("%lld\n",ask2(x2,y2)-ask2(x2,y1-1)-ask2(x1-1,y2)+ask2(x1-1,y1-1));
	}
	return 0;
}
