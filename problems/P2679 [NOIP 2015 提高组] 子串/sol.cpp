#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k;
int f[2][205][205][2];
const int mod=1e9+7;
string a,b;
signed main(){
    cin>>n>>m>>k;
    cin>>a>>b;
    for(int i=0;i<=1;i++){
        f[i][0][0][0]=1;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int p=1;p<=k;p++){
                if(a[i-1]==b[j-1]){
                    f[i%2][j][p][0]=(f[(i-1)%2][j][p][1]+f[(i-1)%2][j][p][0])%mod;
                    f[i%2][j][p][1] = (f[(i-1)%2][j-1][p][1] + (f[(i-1)%2][j-1][p-1][0] + f[(i-1)%2][j-1][p-1][1]) % mod) % mod;
                }
                else{
                    f[i%2][j][p][1]=0;
                    f[i%2][j][p][0]=(f[(i-1)%2][j][p][1]+f[(i-1)%2][j][p][0])%mod;
                }
            }
        }
    }
    cout<<(f[n%2][m][k][0]+f[n%2][m][k][1])%mod;
    return 0;
}