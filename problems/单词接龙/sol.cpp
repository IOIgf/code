#include<bits/stdc++.h>
using namespace std;
int n,cnt;
string s[100005];
map<char,int>g;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s[i];
        g[s[i][0]]++;
        g[s[i][s[i].size()-1]]++;
    }
    for(int i='a';i<='z';i++){
        if(g[i]&1)cnt++;
    }
    if(cnt!=2){
        cout<<"No";
    }
    else{
        cout<<"Yes";
    }
    return 0;
}