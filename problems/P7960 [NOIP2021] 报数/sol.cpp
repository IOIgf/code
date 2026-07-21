#include<bits/stdc++.h>
using namespace std;
int t,x,cnt;
int vis[100005];
int next[10000005];
bool pd(int n){
    while(n!=0){
        if(n%10==7)return 1;
        n/=10;
    }
    return 0;
}
int main(){
    cin>>t;
    for(int i=1;i<=10000000;i++){
        if(!pd(i)&&!vis[i]){
            vis[i]=++cnt;
            next[cnt]=i;
        }
        else{
            for(int j=i;j<=10000000;j+=i){
                vis[j]=-1;
            }
        }
    }
    while(t--){
        cin>>x;
        if(vis[x]==-1){
            cout<<-1<<endl;
        }
        else{
            cout<<next[vis[x]+1]<<endl;
        }
    }
    return 0;
}
