#include<bits/stdc++.h>
#define N 1005
#define M 10005
using namespace std;
const double eps=1e-10;
int n,m;
double a[M][N],b[M],c[N],ans;
void pivot(int l,int e){
	b[l]/=a[l][e];
	for(int j=1;j<=n;j++) if(j!=e) a[l][j]/=a[l][e];
	a[l][e]=1/a[l][e];
	for(int i=1;i<=m;i++){
		if(i!=l&&abs(a[i][e])>eps){
			b[i]-=a[i][e]*b[l];
			for(int j=1;j<=n;j++) if(j!=e) a[i][j]-=a[i][e]*a[l][j];
			a[i][e]=-a[i][e]*a[l][e];
		}
	}
	ans+=c[e]*b[l];
	for(int j=1;j<=n;j++) if(j!=e) c[j]-=c[e]*a[l][j];
	c[e]=-c[e]*a[l][e];
}
double simplex(){
	while(1){
		int e=1,l=0;
		while(e<=n&&c[e]<eps) e++;
		if(e==n+1) return ans;
		double mn=1e100;
		for(int i=1;i<=m;i++){
			if(a[i][e]>eps&&mn>b[i]/a[i][e]){
				mn=b[i]/a[i][e];
				l=i;
			}
		}
		if(mn==1e100) return 1e100;
		pivot(l,e);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lf",&c[i]);
	for(int i=1;i<=m;i++) {
		int l,r,k;
		scanf("%d%d%d",&l,&r,&k);
		b[i]=k;
		for(int j=l;j<=r;j++) a[i][j]=1;
	}
	printf("%.0lf\n",simplex());
	return 0;
}

/*

线性规划 
xi:第i种志愿者招募的人数

min ∑cixi
∑(sj<=i<=tj)xj>=ai
xi>=0

max ∑aiyi
∑(li<=j<=ri)yj<=ci
yi>=0


*/
