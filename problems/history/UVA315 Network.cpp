#include<bits/stdc++.h>
using namespace std;
const int N=501000;
vector<int>g[N];
int dfn[N],low[N],ins[N],idx,n,m,sz,u;
stack<int>stk;
int cnt[N];
void dfs(int u,int f){
	dfn[u]=low[u]=++idx;
	int ch=0;
	for(auto v:g[u]){
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
	sz+=cnt[u];
}
int main(){
    while(scanf("%d",&n),n){
        //if(u==0)continue;
        int v;
        for(int i=1;i<=n;i++)g[i].clear();
        memset(cnt,0,sizeof(cnt));
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        idx=sz=0;
        while(scanf("%d",&u),u){
            while(1){
                char ch=getchar();
                if(ch=='\n')break;
                scanf("%d",&v);
                g[u].push_back(v);
                g[v].push_back(u);
            }
        }
        for(int i=1;i<=n;i++){
            if(!dfn[i])
                dfs(i,0);
        }
	    cout<<sz<<endl;
    }
	//puts("");
	return 0;
}