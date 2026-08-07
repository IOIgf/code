#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,ans;
char c;
int cnt[1005];
char a[10][10];
int bx[30],by[30],tot;
void dfs(int k){
    if(k>tot){
        for(int i=1;i<=n;i++){
            int s=0;
            for(int j=1;j<=n;j++)
                if(a[i][j]=='R')s++;
            if(s>1)return;
        }
        for(int j=1;j<=n;j++){
            int s=0;
            for(int i=1;i<=n;i++)
                if(a[i][j]=='B')s++;
            if(s>1)return;
        }
        ans=(ans+1)%998442353;
        return;
    }
    dfs(k+1);
    a[bx[k]][by[k]]='R';
    dfs(k+1);
    a[bx[k]][by[k]]='B';
}
int main(){
    cin>>n>>m;
    if(n<=5){
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                a[i][j]='.';
        for(int i=1;i<=m;i++){
            cin>>x>>y>>c;
            a[x][y]=c;
            if(c=='B')bx[++tot]=x,by[tot]=y;
        }
        dfs(1);
        cout<<ans%998442353;
        return 0;
    }
    for(int i=1;i<=m;i++){
        cin>>x>>y>>c;
        if(c=='R')cnt[x]++;
    }
    for(int i=1;i<=n;i++){
        if(cnt[i]>1){
            cout<<0%998442353;
            return 0;
        }
    }
    cout<<1%998442353;
    return 0;
}