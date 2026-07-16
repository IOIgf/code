/*
 * @Author: Milk_Dragon 
 * @Date: 2026-07-16 17:26:09 
 * @Last Modified by:   Milk_Dragon 
 * @Last Modified time: 2026-07-16 17:26:09 
 */
#include<bits/stdc++.h>
using namespace std;
int n,m;
string a,b;
vector<int>pi(string s){
    vector<int>res(s.size());
    for(int i=1;i<s.size();i++){
        int j=res[i-1];
        while(j>0&&s[i]!=s[j])j=res[j-1];
        if(s[i]==s[j])j++;
        res[i]=j;
    }
    return res;
}
int kmp(string a,string b){
    string ss=a+'#'+b;
    int res=0;
    vector<int>cc=pi(ss);
    for(int i=a.size()+1;i<ss.size();i++){
        if(a.size()==cc[i])res++;
    }
    return res;
}
int main(){
    cin>>n>>m;
    cin>>a>>b;
    cout<<kmp(b,a);
    return 0;
}