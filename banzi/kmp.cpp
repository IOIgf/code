/*
 * @Author: Milk_Dragon 
 * @Date: 2026-07-16 16:14:01 
 * @Last Modified by:   Milk_Dragon 
 * @Last Modified time: 2026-07-16 16:14:01 
 */
#include<bits/stdc++.h>
using namespace std;
string s1,s2;
vector<int> border;
vector<int>ans;
vector<int> pi(string s){
    vector<int>res(s.size());
    res[0]=0;
    for(int i=1;i<s.size();i++){
        int j=res[i-1];
        while(j>0&&s[i]!=s[j])j=res[j-1];
        if(s[i]==s[j])j++;
        res[i]=j;
    }
    return res;
}
vector<int> kmp(string a,string b){
    string ss=a+'#'+b;
    vector<int>res;
    vector<int>pii=pi(ss);
    for(int i=a.size()+1;i<ss.size();i++){
        if(pii[i]==a.size())res.push_back(i-2*a.size()+1);
    }
    return res;
}
int main(){
    cin>>s1>>s2;
    ans=kmp(s2,s1);
    border=pi(s2);
    for(auto v:ans)cout<<v<<endl;
    for(auto v:border)cout<<v<<" ";
    return 0;
}