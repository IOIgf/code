/*
 * @Author: Milk_Dragon 
 * @Date: 2026-07-16 19:37:25 
 * @Last Modified by: Milk_Dragon
 * @Last Modified time: 2026-07-16 20:16:14
 */
#include<bits/stdc++.h>
using namespace std;
int n,h,ans;
int a[100005];
deque<int>q;
deque<int>qq;
int main(){
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
            if(q.back()<l)q.pop_back();
            if(qq.back()<l)qq.pop_back();
        }
        ans=max(ans,r-l+1);
    }
    cout<<ans;
    return 0;
}