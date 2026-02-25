/* 
insert(s[i]-'c') £¿£¿£¿ 
ÀëÆ×´íÎó 
*/
#include<iostream>
#include<cstring>
#define N 2000005
using namespace std;
char s[N];
int n,lst,tot;
int t[N][26],fail[N],len[N],cnt[N];
void insert(int c){
	int u=++tot,p=lst;
	len[u]=len[lst]+1;lst=u;cnt[u]++;
	while(p&&t[p][c]==0) t[p][c]=u,p=fail[p];
	if(!p) fail[u]=1;
	else{
		int q=t[p][c];
		if(len[q]==len[p]+1) fail[u]=q;
		else{
			int q2=++tot;
			len[q2]=len[p]+1;fail[q2]=fail[q];
			memcpy(t[q2],t[q],sizeof(t[q]));
			fail[u]=fail[q]=q2;
			while(p&&t[p][c]==q) t[p][c]=q2,p=fail[p];
		}
	}
}
int q[N],deg[N],l,r;
int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	lst=tot=1;
	for(int i=1;i<=n;i++) insert(s[i]-'a');
	for(int i=2;i<=tot;i++) deg[fail[i]]++;
	l=1;
	for(int i=2;i<=tot;i++) if(!deg[i]) q[++r]=i;
	long long ans=0;
	while(l<=r){
		int x=q[l++];
		if(cnt[x]>1)ans=max(ans,1ll*len[x]*cnt[x]);
		cnt[fail[x]]+=cnt[x];
		if(--deg[fail[x]]==0) q[++r]=fail[x];
	}
	printf("%lld\n",ans);
	return 0;
}
