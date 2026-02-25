#include<bits/stdc++.h>
#define N 200005
using namespace std;
double eps=1e-8;
int sgn(double x){
	if(abs(x)<eps) return 0;
	return x<0?-1:1;
}
struct point{
	double x,y;
	point operator +(point b){return {x+b.x,y+b.y};}
	point operator -(point b){return {x-b.x,y-b.y};}
	point operator *(double k){return {x*k,y*k};}
	point operator /(double k){return {x/k,y/k};}
	double operator *(point b){return x*b.y-y*b.x;}
	double operator ^(point b){return x*b.x+y*b.y;}
	bool operator ==(point b){return sgn(x-b.x)*sgn(y-b.y)==0;}
};
double len(point a){return sqrt(a.x*a.x+a.y*a.y);}
double arg(point a){return atan2(a.x,a.y);}
double angle(point a,point b){return acos(a^b/len(a)/len(b));}
bool parallel(point a,point b){return sgn(a*b)==0;}
point rotate(point a,double rad){return {a.x*cos(rad)-a.y*sin(rad),a.x*sin(rad)+a.y*cos(rad)};}
double S(point a,point b,point c){return abs((b-a)*(c-a))/2;}
struct line{
	point p1,p2;
};
int point_line_relation(point p,line v){
	return sgn((p-v.p1)*(v.p2-v.p1));
}//0:p在v上  -1:p在v左侧  1:p在v右侧
bool point_on_seg(point p,line v){
	return sgn((p-v.p1)*(v.p2-v.p1))==0&&sgn((p-v.p1)^(p-v.p2))<=0;
}
double dist(point p,line v){
	return abs((p-v.p1)*(v.p2-v.p1))/len(v.p2-v.p1);
}
int line_relation(line v1,line v2){
	if(parallel(v1.p2-v1.p1,v2.p2-v2.p1)){
		if(point_line_relation(v1.p1,v2)==0) return 0;
		return 1;
	}
	return 2;
}//0:重合 1:平行 2:相交 
point cross_point(point a,point b,point c,point d){
	double s1=(b-a)*(c-a),s2=(b-a)*(d-a);
	return (point){c.x*s2-d.x*s1,c.y*s2-d.y*s1}/(s2-s1);
}
bool cross_segment(point a,point b,point c,point d){
	if(point_on_seg(a,{c,d})||point_on_seg(c,{a,b})) return 1;
	return sgn((b-a)*(c-a))*sgn((b-a)*(d-a))<0&&sgn((d-c)*(a-c))*sgn((d-c)*(b-c))<0;
}
int n;
point a[N];
bool cmp(point a,point b){
	if(abs(a.x-b.x)<eps) return a.y<b.y;
	return a.x<b.x;
}
int st[N],top;
void build(){
	sort(a+1,a+n+1,cmp);
	st[++top]=1;
	for(int i=2;i<=n;i++){
		while(top>1&&sgn((a[i]-a[st[top]])*(a[st[top]]-a[st[top-1]]))>=0) top--;
		st[++top]=i;
	}
	int tmp=top;
	for(int i=n-1;i>=1;i--){
		while(top>tmp&&sgn((a[i]-a[st[top]])*(a[st[top]]-a[st[top-1]]))>=0) top--;
		st[++top]=i;
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lf%lf",&a[i].x,&a[i].y);
	build();
	double ans=0;
	for(int i=1;i<top;i++) ans+=len(a[st[i+1]]-a[st[i]]);
	printf("%.2lf\n",ans);
	return 0;
}


