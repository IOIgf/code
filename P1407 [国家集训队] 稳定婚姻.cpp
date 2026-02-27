#include<bitset>
#include<cstdio>
#include<cctype>
#include<queue>
#include<vector>
#include<cstring>
#include<algorithm>
#include<stack>
#include<map>
#define N 20010
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
#include<iostream>
using std::cin;
using std::cout;
#endif
using std::vector;
using std::stack;
using std::pair;
using std::queue;
using std::sort;
using std::map;
using std::string;
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)
int n,m;
vector<int>g[N];
int dfn[N];
int low[N];
int ins[N];
int w[N];
int idx,cnt;
map<string,int>ys;
stack<int>stk;
string u,v;
int cnnt=1;
void tarjan(int u){
    dfn[u]=low[u]=++idx;
    ins[u]=1;
    stk.push(u);
    for(auto v:g[u]){
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(ins[v])low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u]){
        ++cnt;
        while(1){
            int v=stk.top();
            stk.pop();
            ins[v]=0;
            w[v]=cnt;
            if(v==u)break;
        }
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>u>>v;
        ys[u]=i,ys[v]=i+n;
        g[i].push_back(i+n);
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>u>>v;
        g[ys[v]].push_back(ys[u]);
    }
    for(int i=1;i<=2*n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i=1;i<=n;i++){
        if(w[i]!=w[i+n]){
            cout<<"Safe"<<'\n';
        }
        else cout<<"Unsafe"<<'\n';
    }
	return 0;
}