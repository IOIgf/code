#include<iostream>
#include<cstring>
#define N 500005
using namespace std;
int n;
char s[N];
int t[N][26],fail[N],len[N],siz[N],lst,tot;
int insert(int i,int c){
	int p=lst;
	while(s[i-len[p]-1]!=s[i]) p=fail[p];
	if(t[p][c]) lst=t[p][c];
	else{
		int u=++tot;lst=u;
		int q=fail[p];
		while(s[i-len[q]-1]!=s[i]) q=fail[q];
		fail[u]=t[q][c];
		len[u]=len[p]+2;
		siz[u]=siz[fail[u]]+1;
		t[p][c]=u;
	}
	return siz[lst];
}
int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	int ans=0;
	tot=1;
	len[1]=-1;fail[0]=1;
	for(int i=1;i<=n;i++){
		s[i]=((int)s[i]-97+ans)%26+97;
		ans=insert(i,s[i]-'a');
		printf("%d ",ans);
	}
	return 0;
}
