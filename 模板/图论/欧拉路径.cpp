#include<iostream>
#include<vector>
#include<algorithm>
#define N 200005
using namespace std;
int n,m;
vector<int> v[N];
int pt[N],degin[N],degout[N];
int st[N],ans[N],top,tp;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		v[x].push_back(y);
		degin[y]++;
		degout[x]++;
	}
	int flag=1,s=0,t=0;
	for(int i=1;i<=n;i++) {
		sort(v[i].begin(),v[i].end());
		if(degin[i]==degout[i]) continue;
		if(degin[i]==degout[i]-1) {
			if(s) flag=0;
			else s=i;
		}
		else if(degin[i]==degout[i]+1) {
			if(t) flag=0;
			else t=i;
		}
		else flag=0;
	}
	if(!flag){
		puts("No");
		return 0;
	}
	if(!s) s=1;
	st[++top]=s;
	while(top){
		int x=st[top];
		if(pt[x]<v[x].size()) st[++top]=v[x][pt[x]++];
		else {
			top--;
			ans[++tp]=x;
		}
	}
	for(int i=tp;i>=1;i--) printf("%d ",ans[i]);
	return 0;
}
