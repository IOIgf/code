#include<bits/stdc++.h>
#define N 5005
#define M 200005
using namespace std;
int n,m,k,s,t;
int ax[M],ay[M],edge[M],d[N];
vector<int> v1[N],v2[N];
int pre[N],v[N];
priority_queue<pair<int,int>> q;
void dijkstra(){
	for(int i=1;i<=n;i++) d[i]=0x3f3f3f3f;
	q.push(make_pair(0,t));d[t]=0;
	while(q.size()){
		int x=q.top().second;q.pop();
		if(v[x]) continue;v[x]=1;
		for(int i:v2[x]){
			int y=ax[i];
			if(d[y]>d[x]+edge[i]){
				d[y]=d[x]+edge[i],pre[y]=i;
				q.push(make_pair(-d[y],y));
			}
		}
	}
}
vector<int> son[N];
int ls[M*20],rs[M*20],dst[M*20],num[M*20];
int rt[N],tot2;
int merge(int x,int y){
	if(!x||!y) return x+y;
	if(edge[num[x]]>edge[num[y]]) swap(x,y);
	int p=++tot2;num[p]=num[x];
	ls[p]=ls[x],rs[p]=merge(rs[x],y);
	if(dst[ls[p]]<dst[rs[p]]) swap(ls[p],rs[p]);
	dst[p]=dst[rs[p]]+1;
	return p;
}
void dfs(int x){
	for(int i:v1[x])
		if(i!=pre[x]) rt[x]=merge(rt[x],i);
	for(int y:son[x]) rt[y]=rt[x],dfs(y);
}	
struct node{
	int dis,p;
};
bool operator <(node a,node b){
	return a.dis>b.dis;
}
priority_queue<node> q2;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&ax[i],&ay[i],&edge[i]);
		v1[ax[i]].push_back(i);
		v2[ay[i]].push_back(i);
	}
	scanf("%d%d%d",&s,&t,&k);
	dijkstra();
	if(d[s]==0x3f3f3f3f){
		puts("-1");
		return 0;
	}
	for(int i=1;i<=n;i++)
		if(i!=t) son[ay[pre[i]]].push_back(i);
	for(int i=1;i<=m;i++) {
		edge[i]=d[ay[i]]+edge[i]-d[ax[i]];
		num[i]=i;
	}
	tot2=m;
	dfs(t);
	q2.push({d[s]+edge[num[rt[s]]],rt[s]});
	if(k==1){
		if(s==t) puts("-1");
		else printf("%d\n",d[s]);
		return 0;
	}
	int cnt=(s!=t);
	while(q2.size()){
		node st=q2.top();q2.pop();
		if(st.dis>=0x3f3f3f3f) break;
		if(++cnt==k){
			printf("%d\n",st.dis);
			return 0;
		}
		int y=ay[num[st.p]];
		q2.push({st.dis+edge[num[rt[y]]],rt[y]});
		if(ls[st.p]) q2.push({st.dis-edge[num[st.p]]+edge[num[ls[st.p]]],ls[st.p]});
		if(rs[st.p]) q2.push({st.dis-edge[num[st.p]]+edge[num[rs[st.p]]],rs[st.p]});
	}
	puts("-1");
	return 0;
}
