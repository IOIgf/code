#include<bits/stdc++.h>
#define N 1000005
#define ll long long
using namespace std;
const int P=1000000009,B=13331;
int n,m;
char s[N];
ll p[N],h[N];
ll hs(int l,int r){
	return (h[r]-h[l-1]*p[r-l+1]%P+P)%P;
}
int LCP(int i,int j){
	int l=0,r=n-j+1;
	while(l<r){
		int mid=(l+r+1)/2;
		if(hs(i,i+mid-1)==hs(j,j+mid-1)) l=mid;
		else r=mid-1;
	}
	return l;
}
int LCS(int i,int j){
	int l=0,r=i;
	while(l<r){
		int mid=(l+r+1)/2;
		if(hs(i-mid+1,i)==hs(j-mid+1,j)) l=mid;
		else r=mid-1;
	}
	return l;
}
bool cmp(int i,int j,int flag){
	int len=LCP(i,j);
	if(len==n-j+1) return flag;
	return s[i+len]<s[j+len];
}
int st1[N],top1,st2[N],top2;
struct runs{
	int i,j,p;
}a[N*2],b[N*2];
int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	p[0]=1;
	for(int i=1;i<=n;i++){
		h[i]=(h[i-1]*B+s[i])%P;
		p[i]=p[i-1]*B%P;
	}
	for(int i=n;i>=1;i--){
		while(top1&&cmp(i,st1[top1],0)) top1--;
		st1[++top1]=i;
		while(top2&&!cmp(i,st2[top2],1)) top2--;
		st2[++top2]=i;
		if(top1>1){
			int j=st1[top1-1];
			int len1=LCP(i,j),len2=LCS(i-1,j-1);
			if(len1+len2>=j-i) a[++m]={i-len2,j+len1-1,j-i};
		}
		if(top2>1){
			int j=st2[top2-1];
			int len1=LCP(i,j),len2=LCS(i-1,j-1);
			if(len1+len2>=j-i) a[++m]={i-len2,j+len1-1,j-i};
		}
	}
	sort(a+1,a+m+1,[&](runs a,runs b){return a.i<b.i||a.i==b.i&&(a.j<b.j||a.j==b.j&&a.p<b.p);});
	int cnt=0;
	for(int i=1;i<=m;i++)
		if(a[i].i!=a[i-1].i||a[i].j!=a[i-1].j) b[++cnt]=a[i];
	cout<<cnt,puts("");
	for(int i=1;i<=cnt;i++)
		cout<<b[i].i<<" "<<b[i].j<<" "<<b[i].p,puts("");
	return 0;
}
/*

aababaabab

aabab

*/
