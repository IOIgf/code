#include<bits/stdc++.h>
using namespace std;
int t,l,num,cnt,ans;
string s;
char c1,c2,c3,c4;
int main(){
    cin>>t;
    while(t--){
        cin>>l;
        cin>>s;
        if(s[2]=='1')num=1;
        for(int i=1;i<=l;i++){
            cin>>c1;
            if(c1=='F'){
                cin>>c2>>c3>>c4;
                if(num==1&&c3!=c4){
                    cout<<"No"<<endl;
                    continue;
                }
                if(c4=='n'&&c3!='n'){
                    cnt++;
                }
                else{
                    ans
                }
            }
        }
    }
    return 0;
}