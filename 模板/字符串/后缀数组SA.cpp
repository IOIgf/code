#include<iostream>
#include<cstring>
#define N 2000005
using namespace std;
int n;
char s[N];
int sa[N],rk[N],tmp[N],bin[N],h[N],hei[N];
void sort_tmp(){
	int m=max(n,127);
	memset(bin,0,sizeof(int)*(m+1));
	for(int i=1;i<=n;i++) bin[rk[tmp[i]]]++;
	for(int i=1;i<=m;i++) bin[i]+=bin[i-1];
	for(int i=n;i>=1;i--) sa[bin[rk[tmp[i]]]--]=tmp[i];
}
void SA(){
	for(int i=1;i<=n;i++) tmp[i]=i,rk[i]=s[i];
	sort_tmp();
	for(int j=1;j<=n;j<<=1){
		int tot=0;
		for(int i=n-j+1;i<=n;i++) tmp[++tot]=i;
		for(int i=1;i<=n;i++) if(sa[i]>j) tmp[++tot]=sa[i]-j;
		sort_tmp();
		tmp[sa[1]]=tot=1;
		for(int i=2;i<=n;i++){
			if(rk[sa[i]]==rk[sa[i-1]]&&rk[sa[i]+j]==rk[sa[i-1]+j]) tmp[sa[i]]=tot;
			else tmp[sa[i]]=++tot;
		}
		memcpy(rk,tmp,sizeof(int)*(n+1));
	}
	for(int i=1;i<=n;i++){
		if(rk[i]==1) {
			h[i]=hei[1]=0;
			continue;
		}
		h[i]=max(0,h[i-1]-1);
		while(i+h[i]<=n&&sa[rk[i]-1]+h[i]<=n&&s[i+h[i]]==s[sa[rk[i]-1]+h[i]]) h[i]++;
		hei[rk[i]]=h[i];
	}
}
int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	SA();
	for(int i=1;i<=n;i++) printf("%d ",sa[i]);
	puts("");
	for(int i=1;i<=n;i++) printf("%d ",hei[i]);
	return 0;
}
