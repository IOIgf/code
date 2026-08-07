#include<bits/stdc++.h>
using namespace std;
int t,l,ans,mi;
string s,o,v,x,y;
bool err;
map<char,bool>u;
stack<pair<int,bool>>c;
stack<char>n;
int main(){
    cin>>t;
    while(t--){
        cin>>l>>s;
        mi=0;
        if(s[2]=='1')mi=0;
        else for(int i=4;s[i]!=')';i++)mi=mi*10+s[i]-'0';
        err=0,ans=0;
        int cur=0;
        u.clear();
        while(!c.empty())c.pop();
        while(!n.empty())n.pop();
        for(int i=0;i<l;i++){
            cin>>o;
            if(o=="F"){
                cin>>v>>x>>y;
                if(u[v[0]])err=1;
                u[v[0]]=1;
                n.push(v[0]);
                int a=0;
                bool e=1;
                if(x=="n"&&y=="n")a=0,e=1;
                else if(x=="n"&&y!="n")a=0,e=0;
                else if(x!="n"&&y=="n")a=1,e=1;
                else{
                    int p=stoi(x),q=stoi(y);
                    if(p<=q)a=0,e=1;
                    else a=0,e=0;
                }
                if(!c.empty()&&!c.top().second)e=0;
                if(e&&a==1)cur++;
                ans=max(ans,cur);
                c.push({a,e});
            }
            else{
                if(c.empty()||n.empty())err=1;
                else{
                    if(c.top().second&&c.top().first==1)cur--;
                    u[n.top()]=0;
                    c.pop();
                    n.pop();
                }
            }
        }
        if(!c.empty()||!n.empty())err=1;
        if(err)cout<<"ERR\n";
        else if(ans==mi)cout<<"Yes\n";
        else cout<<"No\n";
    }
}