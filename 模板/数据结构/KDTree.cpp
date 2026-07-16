#include<iostream>
#include<algorithm>
#include<vector>
#define N 200005
using namespace std;
int n,lst,top,m;
struct point{
	int x,y,z;
}a[N];
bool cmpx(point a,point b){return a.x<b.x;}
bool cmpy(point a,point b){return a.y<b.y;}
struct KDtree{
	int L,R,siz;
	vector<int> ls,rs,sum,lx,ly,rx,ry;
	void update(int p,int q){
		sum[p]+=sum[q];
		lx[p]=min(lx[p],lx[q]),ly[p]=min(ly[p],ly[q]);
		rx[p]=max(rx[p],rx[q]),ry[p]=max(ry[p],ry[q]);
	}
	int build(int l,int r,bool f){
		if(l>r) return 0;
		int mid=(l+r)/2;
		if(l<r){
			nth_element(a+l+L-1,a+mid+L-1,a+r+L,f?cmpx:cmpy);
			ls[mid]=build(l,mid-1,!f),rs[mid]=build(mid+1,r,!f);
		}
		lx[mid]=rx[mid]=a[mid+L-1].x;
		ly[mid]=ry[mid]=a[mid+L-1].y;
		sum[mid]=a[mid+L-1].z;
		if(ls[mid]) update(mid,ls[mid]);
		if(rs[mid]) update(mid,rs[mid]);
		return mid;
	}
	int ask(int l,int r,int x1,int y1,int x2,int y2){
		if(l>r) return 0;
		int mid=(l+r)/2,ans=0;
		if(x2<lx[mid]||x1>rx[mid]||y2<ly[mid]||y1>ry[mid]) return 0;
		if(x1<=lx[mid]&&x2>=rx[mid]&&y1<=ly[mid]&&y2>=ry[mid]) return sum[mid];
		ans+=ask(l,mid-1,x1,y1,x2,y2);
		ans+=ask(mid+1,r,x1,y1,x2,y2);
		if(x1<=a[mid+L-1].x&&x2>=a[mid+L-1].x&&y1<=a[mid+L-1].y&&y2>=a[mid+L-1].y) ans+=a[mid+L-1].z;
		return ans;
	}
	void clear(){
		ls.clear();
		rs.clear();
		lx.clear();
		rx.clear();
		ly.clear();
		ry.clear();
		sum.clear();
	}
	void Build(int l,int r){
		L=l;R=r;siz=r-l+1;
		for(int i=1;i<=siz+1;i++){
			ls.push_back(0);
			rs.push_back(0);
			lx.push_back(0);
			rx.push_back(0);
			ly.push_back(0);
			ry.push_back(0);
			sum.push_back(0);
		}
		build(1,siz,0);
	}
}t[22];
void merge(){
	while(top>1&&t[top].siz==t[top-1].siz){
		int l=t[top-1].L,r=t[top].R;
		t[top].clear();
		t[top-1].clear();
		t[top-1].Build(l,r);
		top--;
	}
}
int main(){
	cin>>n;
	while(1){
		int op,x1,y1,x2,y2;
		scanf("%d",&op);
		if(op==3) return 0;
		scanf("%d%d%d",&x1,&y1,&x2);
		x1^=lst;y1^=lst;x2^=lst;
		if(op==1){
			a[++m].x=x1;a[m].y=y1;a[m].z=x2;
			t[++top].Build(m,m);
			merge();
		}
		if(op==2){
			scanf("%d",&y2);
			y2^=lst;
			lst=0;
			for(int i=1;i<=top;i++)
				lst+=t[i].ask(1,t[i].siz,x1,y1,x2,y2);
			printf("%d\n",lst);
		}
	}
	return 0;
}
