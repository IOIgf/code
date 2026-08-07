#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,nn;
int sol(int n,int cnt){
    int res=0;
    int cc=n;
    while(n>0){
        res+=(n%10);
        n/=10;
    }
    //cout<<res<<endl;
    if(res==cc)return cnt;
    return sol(res,cnt+1);
}
signed main(){
    cin>>t;
    while(t--){
        cin>>nn;
            int nnn=sol(nn,1);
            if(nnn%2){
                cout<<"M"<<endl;
            }
            else cout<<"S"<<endl;
    }
    return 0;
}