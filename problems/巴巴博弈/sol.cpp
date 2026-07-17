#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n;
        if(n&1)cout<<"Yes"<<'\n';
        else cout<<"No"<<'\n';
    }
    return 0;
}