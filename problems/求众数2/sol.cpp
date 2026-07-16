/*
 * @Author: Milk_Dragon 
 * @Date: 2026-07-16 17:04:36 
 * @Last Modified by: Milk_Dragon
 * @Last Modified time: 2026-07-16 21:55:41
 */
//https://newoj.daimayuan.top/p/P483?tid=6749d305a42c919d13e6c9a0
#include<bits/stdc++.h>
using namespace std;
int n;
map<int,int>g;
int ans[200005];
int maxn,a[200005];
int cnt;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        g[a[i]]++;
        maxn=max(maxn,g[a[i]]);
    } 
    for(int i=1;i<=n;i++){
        if(g[a[i]]==maxn){
            ans[++cnt]=a[i];
            g[a[i]]=-1;
        }
    }
    sort(ans+1,ans+cnt+1);
    for(int i=1;i<=cnt;i++)cout<<ans[i]<<" ";
    return 0;
}
