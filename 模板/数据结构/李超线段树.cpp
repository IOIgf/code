#include<bits/stdc++.h>
#define N 100005
using namespace std;
template<typename T> void read(T &x){
	x=0;int f=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) f=(c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	if(f) x=-x;
}
const int M=39989;
const double eps=1e-10;
int n,cnt,lst;
struct lines{
	double k,b;
}a[N];
bool cmp(int i,int j,int x){
	if(abs(a[i].k*x+a[i].b-a[j].k*x-a[j].b)<eps) return i>j;
	return a[i].k*x+a[i].b<a[j].k*x+a[j].b;
}
int val[N*4];
void insert(int p,int l,int r,int L,int R,int num){
	if(l==r){
		if(cmp(val[p],num,l)) val[p]=num;
		return;
	}
	int mid=(l+r)/2;
	if(L<=l&&r<=R){
		if(!val[p]) {val[p]=num;return;}
		if(cmp(val[p],num,mid)) swap(val[p],num);
		if(cmp(val[p],num,l)) insert(p*2,l,mid,L,R,num);
		if(cmp(val[p],num,r)) insert(p*2+1,mid+1,r,L,R,num);
		return;
	}
	if(L<=mid) insert(p*2,l,mid,L,R,num);
	if(R>mid) insert(p*2+1,mid+1,r,L,R,num);
}
int ask(int p,int l,int r,int x){
	if(l==r) return val[p];
	int mid=(l+r)/2;
	int ans=0;
	if(x<=mid) ans=ask(p*2,l,mid,x);
	else ans=ask(p*2+1,mid+1,r,x);
	return cmp(val[p],ans,x)?ans:val[p];
}
int main(){
	read(n);
	a[0].b=-1e10;
	while(n--){
		int op;
		read(op);
		if(op==0){
			int x;
			read(x);
			x=(x+lst-1)%M+1;
			lst=ask(1,1,M,x);
			cout<<lst<<"\n";
		}
		if(op==1){
			int x0,y0,x1,y1;
			read(x0),read(y0),read(x1),read(y1);
			x0=(x0+lst-1)%M+1;
			x1=(x1+lst-1)%M+1;
			y0=(y0+lst-1)%1000000000+1;
			y1=(y1+lst-1)%1000000000+1;
			if(x0>x1) swap(x0,x1),swap(y0,y1);
			cnt++;
			if(x0==x1) a[cnt]={0,max(y0,y1)};
			else {
				a[cnt].k=1.0*(y1-y0)/(x1-x0);
				a[cnt].b=y0-a[cnt].k*x0;
			}
			insert(1,1,M,x0,x1,cnt);
		}
	}
	return 0;
}

