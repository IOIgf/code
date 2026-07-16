/*
 * @Author: Milk_Dragon 
 * @Date: 2026-07-16 19:37:25 
 * @Last Modified by: Milk_Dragon
 * @Last Modified time: 2026-07-16 21:52:48
 */
//https://newoj.daimayuan.top/p/P511?tid=6749d305a42c919d13e6c9a0
#include<bits/stdc++.h>
using namespace std;
int n,h,ans;
int a[100005];
deque<int>q;
deque<int>qq;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>h;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    int l=1;
    for(int r=1;r<=n;r++){
        while(!q.empty()&&a[q.back()]<a[r]){
            q.pop_back();
        }
        q.push_back(r);
        while(!qq.empty()&&a[qq.back()]>a[r]){
            qq.pop_back();
        }
        qq.push_back(r);
        while(!q.empty()&&!qq.empty()&&a[q.front()]-a[qq.front()]>=h){
            l++;
            if(q.front()<l)q.pop_front();
            if(qq.front()<l)qq.pop_front();
        }
        ans=max(ans,r-l+1);
    }
    cout<<ans;
    return 0;
}