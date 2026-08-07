#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[8000005];
int f[8000005];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    f[1]=a[1];
    for(int i=2;i<=n;i++){
        f[i]=min(f[i-1]+a[i],f[i-2]+min(a[i-1],a[i]));
    }
    cout<<f[n];
}