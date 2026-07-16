#include<iostream>
#include<cstring>
#define N 1000005
using namespace std;
char s1[N],s2[N];
int n,m,nxt[N],f[N];
int main(){
	scanf("%s%s",s1+1,s2+1);
	n=strlen(s1+1),m=strlen(s2+1);
	for(int i=2,j=0;i<=m;i++){
		while(j&&s2[i]!=s2[j+1]) j=nxt[j];
		if(s2[i]==s2[j+1]) nxt[i]=++j;
	}
	for(int i=1,j=0;i<=n;i++){
		while(j&&s1[i]!=s2[j+1]) j=nxt[j];
		if(s1[i]==s2[j+1]) f[i]=++j;
		if(f[i]==m) printf("%d\n",i-m+1);
	}
	for(int i=1;i<=m;i++) printf("%d ",nxt[i]);
	return 0;
}
