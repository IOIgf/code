/*
 * @Author: Milk_Dragon 
 * @Date: 2026-07-16 19:05:28 
 * @Last Modified by: Milk_Dragon
 * @Last Modified time: 2026-07-16 21:53:55
 */
//https://newoj.daimayuan.top/p/P493?tid=6749d305a42c919d13e6c9a0
#include<bits/stdc++.h>
using namespace std;
int n,k,b,m;
priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>k>>b;
        q.push({b,k});
    }
    cin>>m;
    while(m--){
        auto [now,k]=q.top();
        q.pop();
        cout<<now<<" ";
        q.push({now+k,k});
    }
    return 0;
}