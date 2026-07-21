#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans,ans2;
int w[200005];
vector<int>g[200005];
signed main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        cin>>w[i];
    }
    for(int i=1;i<=n;i++){
        int c1=0,c2=0,maxn=0,cmax=0;
        for(auto v:g[i]){
            if(w[v]>maxn){
                cmax=maxn;
                maxn=w[v];
            }
            else{
                cmax=max(cmax,w[v]);
            }
            c1+=w[v];
            c2+=w[v]*w[v];
        }
        c1*=c1;
        ans2+=c1-c2;
        ans=max(ans,maxn*cmax);

    }
    cout<<ans<<" "<<ans2%10007;
    return 0;
}
GRANT ALL PRIVILEGES ON `syzoj`.* TO "syzoj"@"localhost" IDENTIFIED BY "IOIis114514";
FLUSH PRIVILEGES;