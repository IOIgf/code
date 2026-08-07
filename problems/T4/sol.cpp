#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
int n,k,a[100005],cnt;
bool f,ff;
int qz[100005];
int fqz[100005];
int L[100005],R[100005];
signed main(){
    cin>>t;
    while(t--){
        cin>>n>>k;
        f=ff=0;
        cnt=0;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            qz[i]=qz[i-1]+a[i];
            if(qz[i]==k){
                f=1;
            }
        }
        if(!f){
            cout<<"Yes"<<" "<<1<<" "<<1<<endl;
            continue;
        }
        L[0]=1;
        for(int i=1;i<=n;i++){
            L[i]=L[i-1]&&(s[i]!=k);
        }
        R[n+1]=1;
        for(int i=n;i>=1;i--){
            R[i]=R[i+1]&&(s[i]!=k);
        }
        for(int l=1;l<=n;l++){
            for(int r=l;r<=n;r++){
                ff=0;
                if(!L[l-1]||!R[r+1])continue;
                int cur=qz[l-1];
                for(int i=r;i>=l;i--){
                    cur+=a[i];
                    if(cur==k){
                        ff=1;
                        break;
                    }
                }
                if(!ff){
                    cout<<"Yes "<<l<<" "<<r<<endl;
                    goto tt;
                }
            }
        }
        cout<<"No"<<endl;
        tt:;
    }
    return 0;
}