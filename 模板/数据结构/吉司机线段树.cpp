#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#define N 500005
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
int n,m,a[N];
inline int read(){
	int x=0,f=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	return x*f;
}
struct SegmentTree{
	int l,r;
	long long mx,se,sum,his,cnt;
	long long l1,l2,l3,l4;
}t[N*4];
void update(int p){
	t[p].sum=t[p*2].sum+t[p*2+1].sum;
	t[p].mx=max(t[p*2].mx,t[p*2+1].mx);
	t[p].his=max(t[p*2].his,t[p*2+1].his);
	if(t[p*2].mx>t[p*2+1].mx) {
		t[p].cnt=t[p*2].cnt;
		t[p].se=max(t[p*2].se,t[p*2+1].mx);
	}
	else if(t[p*2].mx<t[p*2+1].mx){
		t[p].cnt=t[p*2+1].cnt;
		t[p].se=max(t[p*2+1].se,t[p*2].mx);
	}
	else {
		t[p].cnt=t[p*2].cnt+t[p*2+1].cnt;
		t[p].se=max(t[p*2].se,t[p*2+1].se);
	}
}
void build(int p,int l,int r){
	t[p].l=l;t[p].r=r;
	if(l==r){
		t[p].mx=t[p].sum=t[p].his=a[l];
		t[p].cnt=1;t[p].se=-INF;
		return;
	}
	int mid=(l+r)/2;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	update(p);
}
/*
mx,se,sum,his,cnt
l1:当前最大值tag
l2:历史最大值tag
l3:当前非最大值tag
l4:历史非最大值tag 
*/
void pushdown(int p,int l1,int l2,int l3,int l4){
	t[p].sum+=l1*t[p].cnt+l3*(t[p].r-t[p].l+1-t[p].cnt);
	t[p].his=max(t[p].his,t[p].mx+l2);
	t[p].mx+=l1;
	t[p].se+=l3;
	t[p].l2=max(t[p].l2,t[p].l1+l2);
	t[p].l1+=l1;
	t[p].l4=max(t[p].l4,t[p].l3+l4);
	t[p].l3+=l3;
}
void spread(int p){
	if(t[p*2].mx>t[p*2+1].mx){
		pushdown(p*2,t[p].l1,t[p].l2,t[p].l3,t[p].l4);
		pushdown(p*2+1,t[p].l3,t[p].l4,t[p].l3,t[p].l4);
	}
	else if(t[p*2].mx<t[p*2+1].mx){
		pushdown(p*2,t[p].l3,t[p].l4,t[p].l3,t[p].l4);
		pushdown(p*2+1,t[p].l1,t[p].l2,t[p].l3,t[p].l4);
	}
	else{
		pushdown(p*2,t[p].l1,t[p].l2,t[p].l3,t[p].l4);
		pushdown(p*2+1,t[p].l1,t[p].l2,t[p].l3,t[p].l4);
	}
	t[p].l1=t[p].l2=t[p].l3=t[p].l4=0;
}
void changeadd(int p,int l,int r,int k){
	if(l<=t[p].l&&t[p].r<=r){
		t[p].mx+=k;
		t[p].se+=k;
		t[p].sum+=(long long)k*(t[p].r-t[p].l+1);
		t[p].his=max(t[p].his,t[p].mx);
		t[p].l1+=k;
		t[p].l3+=k;
		t[p].l2=max(t[p].l2,t[p].l1);
		t[p].l4=max(t[p].l4,t[p].l3);
		return;
	}
	spread(p);
	int mid=(t[p].l+t[p].r)/2;
	if(l<=mid) changeadd(p*2,l,r,k);
	if(r>mid) changeadd(p*2+1,l,r,k);
	update(p);
}
void changemin(int p,int l,int r,int k){
	if(l<=t[p].l&&t[p].r<=r){
		if(t[p].mx<=k) return;
		if(t[p].mx>k&&t[p].se<k){
			t[p].sum+=(long long)(k-t[p].mx)*t[p].cnt;
			t[p].l1+=k-t[p].mx;
			t[p].mx=k;
			return;
		}
		spread(p);
		changemin(p*2,l,r,k);
		changemin(p*2+1,l,r,k);
		update(p);
		return;
	}
	spread(p);
	int mid=(t[p].l+t[p].r)/2;
	if(l<=mid) changemin(p*2,l,r,k);
	if(r>mid) changemin(p*2+1,l,r,k);
	update(p);
}
long long asksum(int p,int l,int r){
	if(l<=t[p].l&&t[p].r<=r) return t[p].sum;
	spread(p);
	int mid=(t[p].l+t[p].r)/2;
	long long ans=0;
	if(l<=mid) ans+=asksum(p*2,l,r);
	if(r>mid) ans+=asksum(p*2+1,l,r);
	return ans;
}
long long askmax(int p,int l,int r){
	if(l<=t[p].l&&t[p].r<=r) return t[p].mx;
	spread(p);
	int mid=(t[p].l+t[p].r)/2;
	long long ans=-INF;
	if(l<=mid) ans=max(ans,askmax(p*2,l,r));
	if(r>mid) ans=max(ans,askmax(p*2+1,l,r));
	return ans;
}
long long askhis(int p,int l,int r){
	if(l<=t[p].l&&t[p].r<=r) return t[p].his;
	spread(p);
	int mid=(t[p].l+t[p].r)/2;
	long long ans=-INF;
	if(l<=mid) ans=max(ans,askhis(p*2,l,r));
	if(r>mid) ans=max(ans,askhis(p*2+1,l,r));
	return ans;
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	build(1,1,n);
	while(m--){
		int op,l,r,k;
		op=read(),l=read(),r=read();
		if(op<=2) k=read();
		if(op==1) changeadd(1,l,r,k);
		if(op==2) changemin(1,l,r,k);
		if(op==3) printf("%lld\n",asksum(1,l,r));
		if(op==4) printf("%lld\n",askmax(1,l,r));
		if(op==5) printf("%lld\n",askhis(1,l,r));
	}
	return 0;
}
