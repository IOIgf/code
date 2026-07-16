#include<bits/stdc++.h>
#define N 1000005
using namespace std;
template<typename T> void read(T &x){
	x=0;int f=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) f=(c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	if(f) x=-x;
}
int n,m,S,T;
int t[N][5];
int pre[N][5],pos[N][5];
int st[N],siz[N],cnt1[N],cnt;
int id[N],cl[N],tag[N];
queue<int> q;
int perm[N],perm2[N];


int main(){
	freopen("T1.txt","r",stdin);
	freopen("T2.txt","w",stdout);
	read(n),read(m),read(S),read(T);
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++) read(t[i][j]);
	for(int c=0;c<m;c++){
		for(int i=0;i<n;i++) pos[t[i][c]][c]++;
		for(int i=0;i<n;i++) pos[i+1][c]+=pos[i][c];
		for(int i=0;i<n;i++) pre[--pos[t[i][c]][c]][c]=i;
	}
	for(int i=0;i<n;i++) id[i]=i;
	swap(id[n-1],id[T]);
	st[cnt]=0,siz[cnt]=n-1,cnt1[cnt]=0;cnt++;
	st[cnt]=n-1,siz[cnt]=1,cnt1[cnt]=0;cnt++;cl[T]=1;
	q.push(1);
	while(q.size()){
		int x=q.front();q.pop();
		for(int c=0;c<m;c++){
			vector<int> tmp;
			for(int i=st[x];i<st[x]+siz[x];i++){
				for(int k=pos[id[i]][c];k<pos[id[i]+1][c];k++){
					int j=pre[k][c];
					if(!tag[j]){
						if(!cnt1[cl[j]]) tmp.push_back(cl[j]);
						cnt1[cl[j]]++;
						tag[j]=1;
					}
				}
			}
			for(int i:tmp){
				int ti=i;
				if(cnt1[i]!=siz[i]){
					bool flag=(cnt1[i]*2>=siz[i]);
					int mid=partition(id+st[i],id+st[i]+siz[i],[&](int x){return tag[x]==flag;})-id-st[i];
					for(int j=st[i]+mid;j<st[i]+siz[i];j++) cl[id[j]]=cnt;
					q.push(cnt);
					if(!flag) ti=cnt;
					st[cnt]=st[i]+mid,siz[cnt]=siz[i]-mid,cnt1[cnt]=0;cnt++;
					siz[i]=mid;
				}
				cnt1[i]=0;
				for(int j=st[ti];j<st[ti]+siz[ti];j++) tag[id[j]]=0;
			}
		}
	}
	cout<<cnt<<" "<<m<<" "<<cl[S]<<" "<<cl[T]<<"\n";
	for(int i=0;i<cnt;i++){
		int x=id[st[i]];
		for(int c=0;c<m;c++) cout<<cl[t[x][c]]<<" ";
		cout<<"\n";
	}
	return 0;
}


/*

下标从 0 开始 
认为 s 是起始状态，t 是唯一的接受状态 

*/

