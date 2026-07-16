#include<bits/stdc++.h>
using namespace std;
int n;
unordered_map<int, int> f;
int ans;
int main(){
    cin>>n;
    
    for(int i=1;i<=n;i++){
        int a;
        cin>>a;
        f[a]=max(f[a],f[a-1]+1);
        ans=max(ans,f[a]);
    }
    cout<<ans<<endl;
}