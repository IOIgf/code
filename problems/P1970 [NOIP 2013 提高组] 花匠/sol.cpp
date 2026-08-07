#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int h[100005];
int up=1,down=1;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>h[i];
    }
    for(int i=2;i<=n;i++){
        if(h[i]>h[i-1]){
            up=down+1;
        }
        if(h[i]<h[i-1]){
            down=up+1;
        }
    }
    cout<<max(up,down);
    return 0;
}