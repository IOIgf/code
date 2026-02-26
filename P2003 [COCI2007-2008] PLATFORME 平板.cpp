#include<bits/stdc++.h>
#define N 1003
typedef long long ll;
#ifdef ONLINE_JUDGE
struct FastIO {
	static const int S=1<<20;
	char wbuf[S];
	int wpos;
	FastIO():wpos(0) {}
	inline char rchar() {
		static char buf[S],*p1=buf,*p2=buf;
		return p1==p2&&(p2=(p1=buf)+fread(buf,1,S,stdin),p1==p2)?EOF:*p1++;
	}
	inline void wchar(char c) {
		if(wpos==S) {
			fwrite(wbuf,1,S,stdout);
			wpos=0;
		}
		wbuf[wpos++]=c;
	}
	inline int read_int() {
		int x=0,s=1;
		char c=rchar();
		while(!isdigit(c)&&c!='-')c=rchar();
		if(c=='-')s=-1,c=rchar();
		while(isdigit(c))x=x*10+(c-'0'),c=rchar();
		return x*s;
	}
	inline unsigned read_uint() {
		unsigned x=0;
		char c=rchar();
		while(!isdigit(c))c=rchar();
		while(isdigit(c))x=x*10+(c-'0'),c=rchar();
		return x;
	}
	inline long long read_ll() {
		long long x=0,s=1;
		char c=rchar();
		while(!isdigit(c)&&c!='-')c=rchar();
		if(c=='-')s=-1,c=rchar();
		while(isdigit(c))x=x*10+(c-'0'),c=rchar();
		return x*s;
	}
	inline double read_db() {
		double x=0,y=1;
		int s=1;
		char c=rchar();
		while(!isdigit(c)&&c!='-'&&c!='.')c=rchar();
		if(c=='-')s=-1,c=rchar();
		if(c=='.') {
			c=rchar();
			while(isdigit(c))x+=(y*=0.1)*(c-'0'),c=rchar();
			return x*s;
		}
		while(isdigit(c))x=x*10+(c-'0'),c=rchar();
		if(c=='.') {
			c=rchar();
			while(isdigit(c))x+=(y*=0.1)*(c-'0'),c=rchar();
		}
		return x*s;
	}
	inline void write_int(int x) {
		if(x<0)wchar('-'),x=-x;
		if(x>9)write_int(x/10);
		wchar(x%10+'0');
	}
	inline void write_uint(unsigned x) {
		if(x>9)write_uint(x/10);
		wchar(x%10+'0');
	}
	inline void write_ll(long long x) {
		if(x<0)wchar('-'),x=-x;
		if(x>9)write_ll(x/10);
		wchar(x%10+'0');
	}
	inline void write_str(const char* s) {
		while(*s)wchar(*s++);
	}
	FastIO& operator>>(int& x) {
		x=read_int();
		return*this;
	}
	FastIO& operator>>(unsigned& x) {
		x=read_uint();
		return*this;
	}
	FastIO& operator>>(long long& x) {
		x=read_ll();
		return*this;
	}
	FastIO& operator>>(double& x) {
		x=read_db();
		return*this;
	}
	FastIO& operator<<(int x) {
		write_int(x);
		return*this;
	}
	FastIO& operator<<(unsigned x) {
		write_uint(x);
		return*this;
	}
	FastIO& operator<<(long long x) {
		write_ll(x);
		return*this;
	}
	FastIO& operator<<(double x) {
		printf("double not supported");
		return*this;
	}
	FastIO& operator<<(char c) {
		wchar(c);
		return*this;
	}
	FastIO& operator<<(const char* s) {
		write_str(s);
		return*this;
	}
	~FastIO() {
		if(wpos)fwrite(wbuf,1,wpos,stdout);
	}
} io;
#define cin io
#define cout io
#else
using std::cin;
using std::cout;
#endif
int n[0],ans[0],d[10001];
struct pingban{
	int h,l,r;
}a[101];
bool cmp(pingban a,pingban b){
	return a.h<b.h;
}
int abss(int x){
    if(x<0){
        return -x;
    }  
    return x;
}
int main(){
	cin>>n[0];
	for(int i=1;i<=n[0];i++){
		cin>>a[i].h>>a[i].l>>a[i].r;
		a[i].r--;
	}
	std::sort(a+1,a+n[0]+1,cmp);
	for(int i=1;i<=n[0];i++){
		ans[0]+=abss(d[a[i].l]-a[i].h);
		ans[0]+=abss(d[a[i].r]-a[i].h);
		for(int j=a[i].l;j<=a[i].r;j++){
			d[j]=a[i].h;
		}
	}
	cout<<ans[0];
}