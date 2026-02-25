#include<bits/stdc++.h>
#define N 1000005
#define ll long long
using namespace std;
template<typename T> void read(T &x){
	x=0;int f=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) f=(c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	if(f) x=-x;
}
int T,n,m,a[N];
int cnt[N];
vector<int> pl[N];
ll f[N];

struct SegmentTree{
	int l,r;
	ll k,b,dx,tag;
}t[N*4];
void update(int p){
	t[p].dx=min(t[p*2].dx,t[p*2+1].dx);
	ll k1=t[p*2].k,b1=t[p*2].b,k2=t[p*2+1].k,b2=t[p*2+1].b;
	if(b1<b2) swap(k1,k2),swap(b1,b2);
	t[p].k=k1,t[p].b=b1;
	if(k2>k1) t[p].dx=min(t[p].dx,(b1-b2)/(k2-k1)+1);
}
void build(int p,int l,int r){
	t[p].l=l;t[p].r=r;
	t[p].k=t[p].b=t[p].dx=t[p].tag=0;
	if(l==r){
		t[p].k=a[l];
		t[p].b=-1ll*a[l]*cnt[l];
		t[p].dx=0x3f3f3f3f;
		return;
	}
	int mid=(l+r)/2;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	update(p);
}
void spread(int p){
	if(t[p].tag){
		t[p*2].dx-=t[p].tag;
		t[p*2+1].dx-=t[p].tag;
		t[p*2].tag+=t[p].tag;
		t[p*2+1].tag+=t[p].tag;
		t[p*2].b+=t[p*2].k*t[p].tag;
		t[p*2+1].b+=t[p*2+1].k*t[p].tag;
		t[p].tag=0;
	}
}
void change1(int p,int l,int r,int k){
	if(l<=t[p].l&&t[p].r<=r){
		if(k<t[p].dx){
			t[p].dx-=k;
			t[p].tag+=k;
			t[p].b+=t[p].k*k;
			return;
		}
		spread(p);
		change1(p*2,l,r,k);
		change1(p*2+1,l,r,k);
		update(p);
		return;
	}
	spread(p);
	int mid=(t[p].l+t[p].r)/2;
	if(l<=mid) change1(p*2,l,r,k);
	if(r>mid) change1(p*2+1,l,r,k);
	update(p);
}
void change2(int p,int x,ll k){
	if(t[p].l==t[p].r){
		t[p].b+=k;
		return;
	}
	spread(p);
	int mid=(t[p].l+t[p].r)/2;
	if(x<=mid) change2(p*2,x,k);
	else change2(p*2+1,x,k);
	update(p);
}
ll ask(int p,int l,int r){
	if(l<=t[p].l&&t[p].r<=r) return t[p].b;
	spread(p);
	int mid=(t[p].l+t[p].r)/2;
	if(r<=mid) return ask(p*2,l,r);
	if(l>mid) return ask(p*2+1,l,r);
	return max(ask(p*2,l,r),ask(p*2+1,l,r));
}


int main(){
	read(T);
	while(T--){
		read(n),read(m);
		for(int i=1;i<=n;i++){
			int l,r;
			read(l),read(r);
			pl[r].push_back(l);
			cnt[l]++,cnt[r+1]--;
		}
		for(int i=1;i<=m;i++) read(a[i]),cnt[i]+=cnt[i-1];
		cnt[m+1]=0;
		build(1,1,m);
		ll ans=0;
		for(int i=1;i<=m;i++){
			if(i>1) f[i]=ask(1,1,i-1);
			f[i]+=1ll*a[i]*cnt[i];
			ans=max(ans,f[i]);
			change2(1,i,f[i]);
			for(int l:pl[i]) change1(1,l,i,1);
		}
		printf("%lld\n",ans);
		for(int i=1;i<=m;i++) cnt[i]=f[i]=0,pl[i].clear();
	}
	return 0;
}

/*

从左往右扫
x[j]:l<=j,i<=r的区间个数
cnt[i]:l<=i<=r的区间个数 
f[i]=max(j<i)(f[j]-p[j]*x[j])+p[i]*cnt[i]
x[j]初始值为cnt[j]
扫到r后将[l,r]中的x[j]-1 

KTT


*/
