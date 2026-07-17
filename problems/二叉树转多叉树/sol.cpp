/*
 * @Author: Milk_Dragon 
 * @Date: 2026-07-16 21:51:14 
 * @Last Modified by: Milk_Dragon
 * @Last Modified time: 2026-07-17 08:03:37
 */
//https://newoj.daimayuan.top/p/P1537?tid=6749d305a42c919d13e6c9a0
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int l[100005],r[100005];
int f[100005];
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>x>>y;
        l[i]=x,r[i]=y;
    }
    for(int i=1;i<=n;i++){
        int p=l[i];
        while(p!=0){
            f[p]=i;
            p=r[p];
        }
    }
    for(int i=2;i<=n;i++){
        cout<<f[i]<<" ";
    }
    return 0;
}