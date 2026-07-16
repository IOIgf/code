/*
 * @Author: Milk_Dragon 
 * @Date: 2026-07-16 19:05:28 
 * @Last Modified by: Milk_Dragon
 * @Last Modified time: 2026-07-16 19:35:11
 */
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