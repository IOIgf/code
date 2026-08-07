#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int p[N],sum[N];
int ask(string op,int i,int j){
	cout<<"? "<<op<<" "<<i<<" "<<j<<endl;
	int x;
    cin>>x;
	if(x==-1)exit(0);
	return x;
}
int main(){
	int n,k;
	cin>>n>>k;
	p[1]=ask("or",1,2);
	sum[2]=p[1]+ask("and",1,2);
	for(int i=3;i<=n;i++){
		int o=ask("or",1,i);
		p[1]&=o;
		sum[i]=o+ask("and",1,i);
	}
	for(int i=2;i<=n;i++)p[i]=sum[i]-p[1];
	cout<<"! ";
	for(int i=1;i<=n;i++)cout<<p[i]<<" ";
	cout<<endl;
}