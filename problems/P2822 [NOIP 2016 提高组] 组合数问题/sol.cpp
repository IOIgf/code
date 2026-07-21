#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll t,flag[2002][2002];
int k,f[2002][2002];
void yh(){
	f[0][0]=f[1][0]=f[1][1]=1;
	for (int i=2;i<=2000;i++){
		f[i][0]=1;
		for (int j=1;j<=i;j++){
			f[i][j]=(f[i-1][j-1]%k+f[i-1][j]%k)%k;
			flag[i][j]=flag[i-1][j]+flag[i][j-1]-flag[i-1][j-1];
			if (f[i][j]==0) flag[i][j]++;
		}
		flag[i][i+1]=flag[i][i];
	}
}
int main (){
	cin>>t>>k;
	yh();
	while (t--){
		int m,n;
		cin>>n>>m;
		if(m>n) cout<<flag[n][n]<<"\n";
		else cout<<flag[n][m]<<"\n";
	}
	return 0;
}