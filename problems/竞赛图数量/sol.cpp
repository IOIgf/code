/*
 * @Author: Milk_Dragon 
 * @Date: 2026-07-17 08:51:42 
 * @Last Modified by: Milk_Dragon
 * @Last Modified time: 2026-07-17 08:54:22
 */
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int qpow(int a,int b){
    int res=1;
    while(b!=0){
        if(b&1)res*=a;
        a*=a;
        b>>=1;
    }
    return res;
}
signed main(){
    cin>>n;
    cout<<qpow(2,(n-1)*n/2);
    return 0;
}