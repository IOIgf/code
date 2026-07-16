#include<bits/stdc++.h>
#define N 600005
#define ll long long
#define mod 1000000007
using namespace std;
template<typename T> void read(T &x){
	x=0;int f=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) f=(c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	if(f) x=-x;
}

struct C{long double x,y;};
C operator +(C a,C b){return {a.x+b.x,a.y+b.y};}
C operator -(C a,C b){return {a.x-b.x,a.y-b.y};}
C operator *(C a,C b){return {a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x};}
const double PI=acos(-1);
int rev[N];
C W[N];
void prework(int M){
	for(int i=0;i<M;i++){
		rev[i]=rev[i>>1]>>1;
		if(i&1) rev[i]+=M/2;
		W[i]={cos(2*PI*i/M),sin(2*PI*i/M)};
	}
}
void FFT(C *f,int M,int flag){
	for(int i=0;i<M;i++) if(i<rev[i]) swap(f[i],f[rev[i]]);
	for(int step=2;step<=M;step<<=1){
		int wn=M/step;
		for(int k=0;k<M;k+=step){
			int w=0;
			for(int i=k;i<k+step/2;i++){
				C a=f[i],b=f[i+step/2]*W[w];
				f[i]=a+b;
				f[i+step/2]=a-b;
				w+=wn;
			}
		}
	}
	if(flag){
		reverse(f+1,f+M);
		for(int i=0;i<M;i++) f[i].x/=M,f[i].y/=M;
	}
}
C mtt1[N],mtt2[N],mtt3[N];
void MTT(ll *f,ll *g,int M){
	for(int i=0;i<M;i++) {
		mtt1[i]={f[i]&((1<<15)-1),f[i]>>15};
		mtt2[i]={g[i]&((1<<15)-1),g[i]>>15};
	}
	prework(M);
	FFT(mtt1,M,0);
	FFT(mtt2,M,0);
	for(int i=0;i<M;i++) mtt3[i]={mtt1[(M-i)%M].x,-mtt1[(M-i)%M].y};
	for(int i=0;i<M;i++){
		C p1=mtt1[i],q=mtt2[i],p2=mtt3[i];
		mtt1[i]=p1*q,mtt2[i]=p2*q;
	}
	FFT(mtt1,M,1);
	FFT(mtt2,M,1);
	for(int i=0;i<M;i++){
		ll a1b1=(ll)round(mtt1[i].x+mtt2[i].x)/2%mod;
		ll a2b2=(ll)round(mtt2[i].x-mtt1[i].x)/2%mod;
		ll a1b2=(ll)round(mtt1[i].y+mtt2[i].y)/2%mod;
		ll a2b1=(ll)round(mtt1[i].y-mtt2[i].y)/2%mod;
		f[i]=(((a2b2<<30)+(a1b2+a2b1<<15)+a1b1)%mod+mod)%mod;
	}
}
ll qmi(ll a,ll b){
	ll ans=1;
	for(;b;b>>=1,a=a*a%mod) if(b&1) ans=ans*a%mod;
	return ans;
}
ll t1[N],t2[N];
void polyinv(ll *f,ll *g,int M){
	g[0]=qmi(f[0],mod-2);
	for(int len=2;len<=M;len<<=1){
		for(int i=0;i<len*2;i++) t1[i]=t2[i]=0;
		for(int i=0;i<len;i++) t1[i]=f[i];
		for(int i=0;i<len/2;i++) t2[i]=g[i];
		MTT(t1,t2,len*2);
		for(int i=0;i<len*2;i++) t1[i]=((i==0)*2-t1[i]+mod)%mod;
		MTT(t2,t1,len*2);
		for(int i=0;i<len;i++) g[i]=t2[i];
	}
}

int n,M=1;
ll f[N],g[N];
int main(){
	read(n);
	while(M<=n) M<<=1;
	for(int i=0;i<n;i++) read(f[i]);
	polyinv(f,g,M);
	for(int i=0;i<n;i++) cout<<g[i]<<" ";
	return 0;
}


