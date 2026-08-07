#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,q,t,cnt,qq;
int u,v;
queue<int>q1,q2,q3;
int a[100005];
bool cmp(int x,int y){
    return x>y;
}
signed main(){
    cin>>n>>m>>q>>u>>v>>t;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++){
        q1.push(a[i]);
    }
    for(int i=1;i<=m;i++){
        int now=-0x3f3f3f3f3f3f3f3f;
        if(!q1.empty())now=max(now,q1.front());
        if(!q2.empty())now=max(now,q2.front());
        if(!q3.empty())now=max(now,q3.front());
        if(!q1.empty()&&now==q1.front()){
            q1.pop();
        }
        else if(!q2.empty()&&now==q2.front())q2.pop();
        else if(!q3.empty())q3.pop();
        now+=qq;
        if(i%t==0){
            cout<<now<<" ";
        }
        qq+=q;
        q2.push((int)(now*u/v)-qq);
        q3.push(now-(int)(now*u/v)-qq);
    }
    cout<<endl;
    while(!q1.empty()||!q2.empty()||!q3.empty()){
        ++cnt;
        int q11=-0x3f3f3f3f3f3f3f3f,q22=-0x3f3f3f3f3f3f3f3f,q33=-0x3f3f3f3f3f3f3f3f,maxn=-0x3f3f3f3f3f3f3f3f;
        if(!q1.empty()&&q1.front()>maxn)maxn=q1.front();
        if(!q2.empty()&&q2.front()>maxn)maxn=q2.front();
        if(!q3.empty()&&q3.front()>maxn)maxn=q3.front();
        if(!q1.empty()&&q1.front()==maxn)q1.pop();
        else if(!q2.empty()&&q2.front()==maxn)q2.pop();
        else if(!q3.empty()&&q3.front()==maxn)q3.pop();
        if(cnt%t==0)cout<<maxn+qq<<" ";
    }
    return 0;
}