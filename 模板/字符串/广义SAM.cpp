#include<bits/stdc++.h>
#define N 1000005
using namespace std;
int n;
int t[N][26],fail[N],len[N],tot=1;
void ins(string s){
	int p=1;
	for(int j=0;j<s.size();j++){
		int c=s[j]-'a';
		if(!t[p][c]) t[p][c]=++tot;
		p=t[p][c];
	}
}
void insert(int lst,int c){
	int u=t[lst][c],p=fail[lst];
	len[u]=len[lst]+1;
	while(p&&t[p][c]==0) t[p][c]=u,p=fail[p];
	if(!p) fail[u]=1;
	else{
		int q=t[p][c];
		if(len[q]==len[p]+1) fail[u]=q;
		else{
			int q2=++tot;
			len[q2]=len[p]+1;fail[q2]=fail[q];
			for(int c=0;c<26;c++) 
				if(len[t[q][c]]) t[q2][c]=t[q][c];
			fail[u]=fail[q]=q2;
			while(p&&t[p][c]==q) t[p][c]=q2,p=fail[p];
		}
	}
}
int qu[N];
void build(){
	int l=1,r=1;qu[1]=1;
	while(l<=r){
		int p=qu[l++];
		for(int c=0;c<26;c++)
			if(t[p][c]) insert(p,c),qu[++r]=t[p][c];
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		ins(s);
	}
	build();
	long long ans=0;
	for(int i=2;i<=tot;i++) ans+=len[i]-len[fail[i]];
	printf("%lld\n%d\n",ans,tot);
	return 0;
}

