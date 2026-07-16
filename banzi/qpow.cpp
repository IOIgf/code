/*
 * @Author: Milk_Dragon 
 * @Date: 2026-07-16 16:13:49 
 * @Last Modified by: Milk_Dragon
 * @Last Modified time: 2026-07-16 17:27:36
 */
#include<bits/stdc++.h>
#define int long 
using namespace std;
int a,b,p;
int qpow(int a,int b){
    int res=1;
    while(b>0){
        if(b&1)res=(res*a)%p;
        a=(a*a)%p;
        b>>=1;
    }
    return res%p;
}
signed main(){
    cin>>a>>b>>p;
    cout<<a<<"^"<<b<<" mod "<<p<<"="<<qpow(a,b);
    return 0;
}
