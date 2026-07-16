#include<bits/stdc++.h>
#define ll long long
#define N 100005
using namespace std;
template<typename T> void read(T &x){
	x=0;int f=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) f=(c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	if(f) x=-x;
}
int n,m;
ll a[N];
ll pos[N],lim[N],H[N],sum2[N];
int del[N];
vector<int> d[N],f[10005][51],vec;

void change1(int i){
	int flag=0;
	while(H[i]>=0){
		sum2[i]=0;
		for(int j:d[pos[i]]) sum2[i]+=((a[j]>>H[i])+1<<H[i])-1;
		if(sum2[i]>=lim[i]) H[i]--,flag=1;
		else break;
	}
	if(H[i]==-1){
		del[i]=1;
		vec.push_back(i);
		return;
	}
	if(flag){
		for(int j:d[pos[i]]) f[j][H[i]].push_back(i);
	}
}

void change2(int x,ll k){
	int h=__lg(a[x]^(a[x]+k));
	a[x]+=k;
	for(int i=0;i<=h;i++){
		vector<int> tmp;
		for(auto num:f[x][i]){
			if(del[num]||i!=H[num]) continue;
			sum2[num]-=((a[x]-k>>i)+1<<i)-1;
			sum2[num]+=((a[x]>>i)+1<<i)-1;
			if(sum2[num]>=lim[num]) change1(num);
			if(!del[num]&&H[num]==i) tmp.push_back(num);
		}
		f[x][i]=tmp;
	}
}

int main(){
	read(n),read(m);
	for(int i=2,n2=0;i<=n;i++){
		if(d[i].size()) continue;
		n2++;
		for(int j=i;j<=n;j+=i) d[j].push_back(n2);
	}
	
	int lst=0,cnt=0;
	while(m--){
		int op;
		read(op);
		if(op==0){
			ll x,y;
			read(x),read(y);
			y^=lst;
			if(y){
				for(int x2:d[x]) change2(x2,y);
			}
			lst=vec.size();
			cout<<lst<<" ";
			sort(vec.begin(),vec.end());
			for(int x:vec) cout<<x<<" ";
			cout<<"\n";
			vec.clear();
		}
		if(op==1){
			cnt++;
			read(pos[cnt]);
			read(lim[cnt]);
			lim[cnt]^=lst;
			if(lim[cnt]==0){
				vec.push_back(cnt);
				continue;
			}
			for(int j:d[pos[cnt]]) lim[cnt]+=a[j];
			H[cnt]=50;
			change1(cnt);
		}
	}
	return 0;
}


