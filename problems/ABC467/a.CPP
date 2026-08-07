#include<bits/stdc++.h>
#define int long long
using namespace std;
int h,w;
double bmi;
signed main(){
    cin>>h>>w;
    bmi=1.0*w/h/h;
    if(bmi*10000>=25){
        cout<<"Yes";
    }
    else cout<<"No";
    return 0;
}