/*
 * @Author: Milk_Dragon 
 * @Date: 2026-07-17 10:55:07 
 * @Last Modified by: Milk_Dragon
 * @Last Modified time: 2026-07-17 11:17:12
 */
#include<bits/stdc++.h>
using namespace std;
int l,s,t,m,n;
int a[105],b[100005];
int f[100005];
int vis[100005];
int ans=INT_MAX;
int main(){
    cin>>l>>s>>t>>m;
    for(int i=1;i<=m;i++)cin>>a[i];
    sort(a+1,a+m+1);
    if(s==t){
        ans=0;
        for(int i=1;i<=m;i++){
            if(a[i]%s==0)ans++;
        }
        cout<<ans;
        return 0;
    }
    for(int i=1;i<=m;i++){
        if(a[i]-a[i-1]>=100){
            b[i]=b[i-1]+100;
        }
        else{
            b[i]=b[i-1]+a[i]-a[i-1];
        }
        vis[b[i]]=1;
        n=max(n,b[i]);
    }
    for(int i=1;i<=n+t-1;i++){
        f[i]=INT_MAX;
        for(int j=s;j<=t;j++){
            if(i-j>=0&&f[i-j]!=INT_MAX){
                f[i]=min(f[i],f[i-j]+vis[i]);
            }
        }
    }
    
    for(int i=n;i<=n+t-1;i++)ans=min(ans,f[i]);
    cout<<ans;
    return 0;
}