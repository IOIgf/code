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
vector<int>e[N];
int dfn[N],low[N],ins[N],idx,n,m,sz;
int cnt[N];
int k;
int cntt;
bool vis[100005];
//stack<int>stk;
//vector<vector<int> >scc;
void dfs(int u,int f){
	dfn[u]=low[u]=++idx;
	int ch=0;
	for(auto v:e[u]){
        if(vis[v])continue;
		if(!dfn[v]){
			dfs(v,u);
			ch++;
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u])cnt[u]=1;
		}
		else if(v!=f){
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(f==0&&ch<=1)cnt[u]=0;
	//sz+=cnt[u];
}
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]){
            if(i==1){
                dfs(i,0);
            }
            else{
                cout<<"Poor SOL!"<<'\n';
                return 0;
            }
        }
	}
    if(k==1){
        for(int i=1;i<=n;i++){
            if(cnt[i]){
                cout<<i<<'\n';
                return 0;
            }
        }
    }
	else if(k==2){
        for(int i=1;i<=n;i++){
            memset(dfn,0,sizeof(dfn));
            memset(low,0,sizeof(low));
            memset(cnt,0,sizeof(cnt));
            idx=0;
            vis[i]=1;
            if(!vis[1]){
                dfs(1,0);
            }
            else dfs(2,0);
            for(int j=1;j<=n;j++){
                if(cnt[j]){
                    cout<<j<<" "<<i<<'\n';
                    return 0;
                }
            }
            vis[i]=0;
        }
    }
    else if(k==3){
        
        for(int i=1;i<=n;i++){
            vis[i]=1;
            for(int k=i+1;k<=n;k++){
                memset(dfn,0,sizeof(dfn));
                memset(low,0,sizeof(low));
                memset(cnt,0,sizeof(cnt));
                idx=0;
                vis[k]=1;
                int s=1;
                while(s==i||s==k)s++;
                dfs(s,0);
                for(int j=1;j<=n;j++){
                    if(cnt[j]){
                        cout<<j<<" "<<i<<" "<<k<<'\n';
                        return 0;
                    }
                }
                vis[k]=0;
            }
            vis[i]=0;
        }
    }
    cout<<"How oversuspicious you are, SOL!"<<'\n';
	return 0;
}