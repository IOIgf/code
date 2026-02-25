#include<bits/stdc++.h>
using namespace std;
const int N=101000;
vector<int>e[N];
int dfn[N],low[N],ins[N],idx,n,m,sz;
int cnt[N];
int k;
int cntt;
bool vis[100005];
//stack<int>stk;
//vector<vector<int> >scc;
void dfs(int u,int f){
	dfn[u]=low[u]=++idx;
	int ch=0;
	for(auto v:e[u]){
        if(vis[v])continue;
		if(!dfn[v]){
			dfs(v,u);
			ch++;
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u])cnt[u]=1;
		}
		else if(v!=f){
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(f==0&&ch<=1)cnt[u]=0;
	//sz+=cnt[u];
}
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]){
            if(i==1){
                dfs(i,0);
            }
            else{
                cout<<"Poor SOL!"<<endl;
                return 0;
            }
        }
	}
    if(k==1){
        for(int i=1;i<=n;i++){
            if(cnt[i]){
                cout<<i<<endl;
                return 0;
            }
        }
    }
	else if(k==2){
        for(int i=1;i<=n;i++){
            memset(dfn,0,sizeof(dfn));
            memset(low,0,sizeof(low));
            memset(cnt,0,sizeof(cnt));
            idx=0;
            vis[i]=1;
            if(!vis[1]){
                dfs(1,0);
            }
            else dfs(2,0);
            for(int j=1;j<=n;j++){
                if(cnt[j]){
                    cout<<j<<" "<<i<<endl;
                    return 0;
                }
            }
            vis[i]=0;
        }
    }
    else if(k==3){
        
        for(int i=1;i<=n;i++){
            vis[i]=1;
            for(int k=i+1;k<=n;k++){
                memset(dfn,0,sizeof(dfn));
                memset(low,0,sizeof(low));
                memset(cnt,0,sizeof(cnt));
                idx=0;
                vis[k]=1;
                int s=1;
                while(s==i||s==k)s++;
                dfs(s,0);
                for(int j=1;j<=n;j++){
                    if(cnt[j]){
                        cout<<j<<" "<<i<<" "<<k<<endl;
                        return 0;
                    }
                }
                vis[k]=0;
            }
            vis[i]=0;
        }
    }
    cout<<"How oversuspicious you are, SOL!"<<endl;
	return 0;
}