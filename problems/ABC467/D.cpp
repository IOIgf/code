#include<bits/stdc++.h>
using namespace std;
int t;
long double px,py,qx,qy,rx,ry,sx,sy;
bool eq(long double a,long double b){return fabsl(a-b)<1e-9;}
int main(){
    cin>>t;
    while(t--){
        cin>>px>>py>>qx>>qy>>rx>>ry>>sx>>sy;
        long double a1=px-qx,b1=py-qy;
        long double a2=rx-sx,b2=ry-sy;
        long double c1=(px*px+py*py-qx*qx-qy*qy)/2;
        long double c2=(rx*rx+ry*ry-sx*sx-sy*sy)/2;
        bool parallel=eq(a1*b2,a2*b1);
        bool same=parallel&&eq(a1*c2,a2*c1)&&eq(b1*c2,b2*c1);
        if(!parallel||same)cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
    return 0;
}