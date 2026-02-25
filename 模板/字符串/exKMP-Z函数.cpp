#include<iostream>
#include<cstring>
#define N 40000005
using namespace std;
char s1[N],s2[N];
int n,m,z[N];
void zfunc(){
	int c=0,r=0;
	for(int i=2;i<=n+m+1;i++){
		if(i<=r) z[i]=min(r-i+1,z[i-c+1]);
		while(s1[i+z[i]]==s1[z[i]+1]) z[i]++;
		if(i+z[i]-1>r) c=i,r=i+z[i]-1;
	}
}
int main(){
	scanf("%s%s",s2+1,s1+1);
	n=strlen(s1+1),m=strlen(s2+1);
	s1[n+1]='#';
	for(int i=1;i<=m;i++) s1[n+i+1]=s2[i];
	zfunc();
	long long ans1=n+1,ans2=0;
	for(int i=2;i<=n;i++) ans1^=1ll*i*(z[i]+1);
	for(int i=1;i<=m;i++) ans2^=1ll*i*(z[n+i+1]+1);
	printf("%lld\n%lld\n",ans1,ans2);
	return 0;
}
