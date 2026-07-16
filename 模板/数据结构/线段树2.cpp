#include<iostream>
#define N 100005
using namespace std;
int n,q,mod,a[N];
struct SegmentTree{
	int l,r;
	long long sum,add,mul;
}t[N*4];
void build(int p,int l,int r){
	t[p].l=l;t[p].r=r;t[p].mul=1;
	if(l==r) {t[p].sum=a[l];return;}
	int mid=(l+r)/2;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	t[p].sum=(t[p*2].sum+t[p*2+1].sum)%mod;
}
void spread(int p){
	if(t[p].mul!=1){
		t[p*2].mul=t[p*2].mul*t[p].mul%mod;
		t[p*2+1].mul=t[p*2+1].mul*t[p].mul%mod;
		t[p*2].add=t[p*2].add*t[p].mul%mod;
		t[p*2+1].add=t[p*2+1].add*t[p].mul%mod;
		t[p*2].sum=t[p*2].sum*t[p].mul%mod;
		t[p*2+1].sum=t[p*2+1].sum*t[p].mul%mod;
		t[p].mul=1;
	}
	if(t[p].add){
		t[p*2].add=(t[p*2].add+t[p].add)%mod;
		t[p*2+1].add=(t[p*2+1].add+t[p].add)%mod;
		t[p*2].sum=(t[p*2].sum+t[p].add*(t[p*2].r-t[p*2].l+1))%mod;
		t[p*2+1].sum=(t[p*2+1].sum+t[p].add*(t[p*2+1].r-t[p*2+1].l+1))%mod;
		t[p].add=0;
	}
}
void change(int p,int l,int r,int k,int op){
	if(l<=t[p].l&&t[p].r<=r){
		if(op==1){
			t[p].mul=t[p].mul*k%mod;
			t[p].add=t[p].add*k%mod;
			t[p].sum=t[p].sum*k%mod;
		}else{
			t[p].add=(t[p].add+k)%mod;
			t[p].sum=(t[p].sum+(long long)k*(t[p].r-t[p].l+1))%mod;
		}
		return;
	}
	spread(p);
	int mid=(t[p].l+t[p].r)/2;
	if(l<=mid) change(p*2,l,r,k,op);
	if(r>mid) change(p*2+1,l,r,k,op);
	t[p].sum=(t[p*2].sum+t[p*2+1].sum)%mod;
}
long long ask(int p,int l,int r){
	if(l<=t[p].l&&t[p].r<=r) return t[p].sum;
	spread(p);
	int mid=(t[p].l+t[p].r)/2;
	long long ans=0;
	if(l<=mid) ans=(ans+ask(p*2,l,r))%mod;
	if(r>mid) ans=(ans+ask(p*2+1,l,r))%mod;
	return ans;
}
int main(){
	scanf("%d%d%d",&n,&q,&mod);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	build(1,1,n);
	while(q--){
		int op,x,y,k;
		scanf("%d%d%d",&op,&x,&y);
		if(op==1){
			scanf("%d",&k);
			change(1,x,y,k,1);
		}
		if(op==2){
			scanf("%d",&k);
			change(1,x,y,k,2);
		}
		if(op==3) printf("%lld\n",ask(1,x,y));
	}
	return 0;
}

/*

18:32~18:42

*/
