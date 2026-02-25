#include<bits/stdc++.h>
using namespace std;
int t,n,a[100005];
bool vis[100005];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		memset(vis,0,sizeof(vis));
		int ans=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				if(a[i]==a[j]&&!vis[j]){
					ans++;
					vis[j]=1;
					break;
				}
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
