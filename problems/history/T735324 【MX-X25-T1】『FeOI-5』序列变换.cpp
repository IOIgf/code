#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,a[N],maxn,cnt;
int mex,aa[N],t,c;
bool vis[N],f;
bool pd(){
    for(int i=2;i<=n;i++){
        if((aa[i]!=0&&aa[i]!=1)||aa[i]!=aa[i-1])return 0;
    }
    return 1;
}
bool pd2(){
    for(int i=2;i<=n;i++){
        if((a[i]!=0&&a[i]!=1)||a[i]!=a[i-1])return 0;
    }
    return 1;
}
int main(){
    cin>>c>>t;
    while(t--){
        cin>>n;
        memset(vis,0,sizeof(vis));
        memset(aa,0,sizeof(aa));
        maxn=0;
        cnt=0;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            // vis[a[i]]=1;
            // maxn=max(maxn,a[i]);
            // for(int j=0;j<=maxn+1;j++){
            //     if(!vis[j]){aa[i]=j;break;}
            // }
            //cout<<aa[i]<<" ";
        }
        if(pd2()){
            cout<<2<<endl;
            continue;
        }
        // for(int i=1;i<=n;i++)a[i]=aa[i];
        //for(int i=1;i<=n;i++)cout<<aa[i]<<" ";
        //cout<<endl<<pd()<<endl;
        while(!pd2()){
            cnt++;
            memset(vis,0,sizeof(vis));
            maxn=0;
            for(int i=1;i<=n;i++){
                vis[a[i]]=1;
                maxn=max(maxn,a[i]);
                for(int j=0;j<=n;j++){
                    if(!vis[j]){aa[i]=j;break;}
                }
            }
            for(int i=1;i<=n;i++)a[i]=aa[i];
        }
        cout<<cnt+2<<endl;
    }
    
    return 0;
}