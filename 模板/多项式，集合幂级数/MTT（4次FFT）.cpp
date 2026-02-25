#include<bits/stdc++.h>
#define N 600005
#define ll long long
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
int rev[N],init;
C W[N];
void FFT(C *f,int M,int flag){
	if(!init){
		for(int i=0;i<M;i++){
			rev[i]=rev[i>>1]>>1;
			if(i&1) rev[i]+=M/2;
			W[i]={cos(2*PI*i/M),sin(2*PI*i/M)};
		}
		init=1;
	}
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
C t1[N],t2[N],t3[N];
void MTT(ll *f,ll *g,int M,int mod){
	for(int i=0;i<M;i++) {
		t1[i]={f[i]&((1<<15)-1),f[i]>>15};
		t2[i]={g[i]&((1<<15)-1),g[i]>>15};
	}
	FFT(t1,M,0);
	FFT(t2,M,0);
	for(int i=0;i<M;i++) t3[i]={t1[(M-i)%M].x,-t1[(M-i)%M].y};
	for(int i=0;i<M;i++){
		C p1=t1[i],q=t2[i],p2=t3[i];
		t1[i]=p1*q,t2[i]=p2*q;
	}
	FFT(t1,M,1);
	FFT(t2,M,1);
	for(int i=0;i<M;i++){
		ll a1b1=(ll)round(t1[i].x+t2[i].x)/2%mod;
		ll a2b2=(ll)round(t2[i].x-t1[i].x)/2%mod;
		ll a1b2=(ll)round(t1[i].y+t2[i].y)/2%mod;
		ll a2b1=(ll)round(t1[i].y-t2[i].y)/2%mod;
		f[i]=(((a2b2<<30)+(a1b2+a2b1<<15)+a1b1)%mod+mod)%mod;
	}
}

int n,m,M=1,mod;
ll f[N],g[N];
int main(){
	read(n),read(m),read(mod);
	while(M<=n+m) M<<=1;
	for(int i=0;i<=n;i++) read(f[i]);
	for(int i=0;i<=m;i++) read(g[i]);
	MTT(f,g,M,mod);
	for(int i=0;i<=n+m;i++) cout<<f[i]<<" ";
	return 0;
}


