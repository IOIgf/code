#include<bits/stdc++.h>
#define ll long long
#define mod 1000000009
using namespace std;
template<typename T> void read(T &x){
	x=0;int f=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) f=(c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	if(f) x=-x;
}
int n,cnt[1<<20];
int a[1<<20][21],b[1<<20][21];
inline int Mod(int x){
	return x>=mod?x-mod:x;
}
int main(){
	read(n);
	for(int i=0;i<(1<<n-1);i++) cnt[i*2]=cnt[i],cnt[i*2+1]=cnt[i]+1;
	for(int i=0;i<(1<<n);i++) read(a[i][cnt[i]]);
	for(int i=0;i<(1<<n);i++) read(b[i][cnt[i]]);
	for(int i=0;i<n;i++)
		for(int j=0;j<(1<<n);j++)
			if(j&(1<<i)){
				for(int k=0;k<=n;k++) a[j][k]=Mod(a[j][k]+a[j-(1<<i)][k]);
				for(int k=0;k<=n;k++) b[j][k]=Mod(b[j][k]+b[j-(1<<i)][k]);
			}
	for(int i=0;i<(1<<n);i++){
		for(int j=n;j>=0;j--){
			ll val=0;
			for(int k=0;k<=j;k++) val+=1ll*a[i][k]*b[i][j-k]%mod;
			a[i][j]=val%mod;
		}
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<(1<<n);j++)
			if(j&(1<<i))
				for(int k=0;k<=n;k++) a[j][k]=Mod(a[j][k]-a[j-(1<<i)][k]+mod);
	for(int i=0;i<(1<<n);i++) cout<<a[i][cnt[i]]<<" ";
	return 0;
}


