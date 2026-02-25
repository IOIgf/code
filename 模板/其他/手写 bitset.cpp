#include<bits/stdc++.h>
#define N 200005
#define M 3130
#define ll unsigned long long
using namespace std;

struct Bitset{
	ll f[M];
	void reset(){memset(f,0,sizeof(f));}
	void set(){memset(f,0,sizeof(f));}
	bool operator[](int x){
		return f[x>>6]>>(x&63)&1;
	}
	void set(int x,int c){
		if(c==1) f[x>>6]|=1ull<<(x&63);
		else f[x>>6]&=~(1ull<<(x&63));
	}
	int count(){
		int ans=0;
		for(int i=0;i<M;i++) ans+=__builtin_popcountll(f[i]);
		return ans;
	}
	
	Bitset operator ~ (void) const{
		Bitset res;
		for(int i=0;i<M;i++) res.f[i]=~f[i];
		return res;
	}
	Bitset operator & (const Bitset &b) const{
		Bitset res;
		for(int i=0;i<M;i++) res.f[i]=f[i]&b.f[i];
		return res;
	}
	Bitset operator | (const Bitset &b) const{
		Bitset res;
		for(int i=0;i<M;i++) res.f[i]=f[i]|b.f[i];
		return res;
	}
	Bitset operator ^ (const Bitset &b) const{
		Bitset res;
		for(int i=0;i<M;i++) res.f[i]=f[i]^b.f[i];
		return res;
	}
	void operator &=(const Bitset &b){
		for(int i=0;i<M;i++) f[i]&=b.f[i];
	}
	void operator |=(const Bitset &b){
		for(int i=0;i<M;i++) f[i]|=b.f[i];
	}
	void operator ^=(const Bitset &b){
		for(int i=0;i<M;i++) f[i]^=b.f[i];
	}
	
	Bitset operator <<(const int t) const{
		Bitset res;
		int h=t>>6,l=t&63;
		ll lst=0;
		for(int i=0;i+h<M;i++){
			res.f[i+h]=lst|(f[i]<<l);
			if(l) lst=f[i]>>64-l;
		}
		for(int i=0;i<h;i++) res.f[i]=-1;
		res.f[h]|=(1ull<<l)-1;
		return res;
	}
	Bitset operator >>(const int t) const{
		Bitset res;
		int h=t>>6,l=t&63;
		ll lst=0;
		for(int i=M-1;i>=h;i--){
			res.f[i-h]=lst|(f[i]>>l);
			if(l) lst=f[i]<<64-l;
		}
		return res;
	}
}F;

int main(){
	
	return 0;
}


