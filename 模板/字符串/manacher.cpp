#include<iostream>
#include<cstring>
#define N 22000005
using namespace std;
char s[N],s2[N];
int n,p[N];
void manacher(){
	s2[0]='%';s2[1]='#';
	for(int i=1;i<=n;i++){
		s2[i*2]=s[i];
		s2[i*2+1]='#';
	}
	s2[n*2+2]='$';
	int c=0,r=0;
	for(int i=1;i<n*2+2;i++){
		if(i<r) p[i]=min(r-i,p[c*2-i]);
		while(s2[i+p[i]+1]==s2[i-p[i]-1]) p[i]++;
		if(i+p[i]>r) c=i,r=i+p[i];
	}
}
int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	manacher();
	int ans=0;
	for(int i=1;i<=n*2+2;i++) ans=max(ans,p[i]);
	printf("%d\n",ans);
	return 0;
}
