#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a,b,ans;
string s;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a>>b>>s;
        if(s=="keep")ans+=b-a;
    }
    cout<<ans;
    return 0;
}