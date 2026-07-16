#include<iostream>
#include<cmath>
#include<algorithm>
#define N 2100005
using namespace std;
const double PI=acos(-1);
int n,m,k,M;
struct C{
	double r,i;
	C operator +(const C &c) const{
		return {r+c.r,i+c.i};
	}
	C operator -(const C &c) const{
		return {r-c.r,i-c.i};
	}
	C operator *(const C &c) const{
		return {r*c.r-i*c.i,r*c.i+i*c.r};
	}
};
C f[N],g[N],w[N];
int rev[N];
void change(C *f){
	for(int i=0;i<M;i++){
		rev[i]=rev[i>>1]>>1;
		if(i&1) rev[i]|=M>>1;
		if(i<rev[i]) swap(f[i],f[rev[i]]);
	}
}
void FFT(C *f,bool flag){
	change(f);
	for(int step=2;step<=M;step<<=1){
		for(int k=0;k<M;k+=step){
			int W=0;
			for(int i=k;i<k+step/2;i++){
				C a=f[i],b=w[W]*f[i+step/2];
				f[i]=a+b;
				f[i+step/2]=a-b;
				W+=M/step;
			}
		}
	}
	if(flag){
		reverse(f+1,f+M);
		for(int i=0;i<M;i++) f[i].r/=M;
	}
}
inline int read(){
	int x=0,f=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	return x*f;
}
int main(){
	n=read(),m=read();
	while((1<<k)<n+m+1) k++;
	M=1<<k;
	for(int i=0;i<=n;i++) f[i].r=read();
	for(int i=0;i<=m;i++) g[i].r=read();
	for(int i=0;i<M;i++) w[i]=C{cos(2*PI*i/M),sin(2*PI*i/M)};
	FFT(f,0);
	FFT(g,0);
	for(int i=0;i<M;i++) f[i]=f[i]*g[i];
	FFT(f,1);
	for(int i=0;i<=n+m;i++) cout<<(int)(f[i].r+0.5)<<" ";
	return 0;
}


