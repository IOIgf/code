#include<iostream>
#include<cstring>
#include<algorithm>
#define N 200005
using namespace std;
int n,tot;
int t[N][26],fail[N];
string s[N],T;
int insert(string s){
	int p=0;
	for(int i=0;i<s.size();i++){
		int c=s[i]-'a';
		if(!t[p][c]) t[p][c]=++tot;
		p=t[p][c];
	}
	return p;
}
int q[N],l,r;
void build(){
	l=1;r=0;
	for(int i=0;i<26;i++) if(t[0][i]) q[++r]=t[0][i];
	while(l<=r){
		int p=q[l++];
		for(int c=0;c<26;c++){
			if(t[p][c]) fail[t[p][c]]=t[fail[p]][c],q[++r]=t[p][c];
			else t[p][c]=t[fail[p]][c];
		}
	}
}
int tag[N],pos[N];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		pos[i]=insert(s[i]);
	} 
	build();
	cin>>T;
	for(int i=0,p=0;i<T.size();i++){
		p=t[p][T[i]-'a'];
		tag[p]++;
	}
	for(int i=r;i>=1;i--)
		tag[fail[q[i]]]+=tag[q[i]];
	for(int i=1;i<=n;i++) printf("%d\n",tag[pos[i]]);
	return 0;
}
