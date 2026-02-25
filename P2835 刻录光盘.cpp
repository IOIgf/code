#include<bits/stdc++.h>
using namespace std;
int n,m;
int fa[100005];
void add(int x,int y){
	fa[x]=y;
}
int main(){
    cin>>n;
    int cnt=0;
    for(int i=1;i<=n;i++)fa[i]=i;
    for(int i=1;i<=n;i++){
        int u;
        while(1){
            cin>>u;
            if(u==0)break;
            add(u,i);
        }
    }
	for(int i=1;i<=n;i++){
        if(fa[i]==i)cnt++;
    }
    if(cnt==0)cout<<cnt+1<<endl;
    else cout<<cnt<<endl;
	return 0;
}