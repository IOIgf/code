#include<bits/stdc++.h>
using namespace std;
const int MAXN=200005;
int a[MAXN],b[MAXN];
int dp[MAXN][2];
int n,m;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n-1;i++)cin>>b[i];
    memset(dp,0x3f,sizeof(dp));
    dp[1][0]=a[1];
    dp[1][1]=1-a[1];
    for(int i=1;i<=n-1;i++){
        for(int r=0;r<2;r++){
            int nxt=r^b[i];
            dp[i+1][nxt]=min(dp[i+1][nxt],dp[i][r]+(a[i+1]^nxt));
        }
    }
    cout<<min(dp[n][0],dp[n][1])<<"\n";
}