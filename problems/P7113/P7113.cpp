/*
 * @Author: Milk_Dragon 
 * @Date: 2026-07-16 16:14:11 
 * @Last Modified by:   Milk_Dragon 
 * @Last Modified time: 2026-07-16 16:14:11 
 */
#include<bits/stdc++.h>
#define I1 __int128
using namespace std;
int n,m;
vector<int>g[100005];
int tot;
int cnt[100005],s[100005];
I1 fz[100005],fm[100005];
int ans[100005],cnnt;
void write(I1 x){
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
I1 gcd(I1 a,I1 b){
    if(b==0)return a;
    return gcd(b,a%b);
}
void tf(I1 u,I1 x,I1 y){
    if(y==0)return;
    I1 fmm=fm[u]*y;
    I1 fzz=fm[u]*x+y*fz[u];
    I1 yf=gcd(fmm,fzz);
    fm[u]=fmm/yf,fz[u]=fzz/yf;
}
void topu(){
    queue<int>q;
    for(int i=1;i<=tot;i++){
        fm[s[i]]=fz[s[i]]=1;
        q.push(s[i]);
    }
    while(!q.empty()){
        int now=q.front();
        //cout<<now<<endl;
        q.pop();
        for(auto v:g[now]){
            cnt[v]--;
            if(cnt[v]==0)q.push(v);
            //cout<<v<<endl;
            tf(v,fz[now],fm[now]*g[now].size());
        }
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int x;
        fm[i]=1;
        cin>>x;
        if(x==0){
            ans[++cnnt]=i;
        }
        for(int j=1;j<=x;j++){
            int u;
            cin>>u;
            g[i].push_back(u);
            cnt[u]++;    
        }
    }
    for(int i=1;i<=n;i++){
        if(cnt[i]==0){
            s[++tot]=i;
        }
    }
    topu();
    for(int i=1;i<=cnnt;i++){
        write(fz[ans[i]]);
        cout<<" ";
        write(fm[ans[i]]);
        cout<<endl;
    }
    return 0;
}
