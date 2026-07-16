/*
 * @Author: Milk_Dragon 
 * @Date: 2026-07-16 21:51:14 
 * @Last Modified by: Milk_Dragon
 * @Last Modified time: 2026-07-16 22:00:28
 */
//https://newoj.daimayuan.top/p/P1537?tid=6749d305a42c919d13e6c9a0
#include<bits/stdc++.h>
using namespace std;
int n;
int l[100005],r[100005];
vector<int>g[100005];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>x>>y;
        l[i]=x,r[i]=y;
        g[x].push_back(i);
        g[y].push_back(i-1);
    }
    for(int i=2;i<=n;i++){
        cout<<g[i][0]<<" ";
    }
    return 0;
}