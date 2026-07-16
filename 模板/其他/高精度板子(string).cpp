#include<iostream>
using namespace std;
int a[10005];
bool cmp(string a,string b){
	if(a.size()==b.size()) return a<b;
	return a.size()<b.size();
}
int adjust1(int len){
	for(int i=1;i<len;i++) if(a[i]>9) a[i+1]+=a[i]/10,a[i]%=10;
	while(a[len]>9) a[len+1]=a[len]/10,a[len++]%=10;
	return len;
}
int adjust2(int len){
	for(int i=1;i<len;i++) if(a[i]<0) a[i]+=10,a[i+1]--;
	while(len>1&&a[len]==0) len--;
	return len;
}
string chg(int len){
	string s3="";
	for(int i=len;i>=1;i--) s3+=a[i]+'0';
	return s3;
}
string operator +(string s1,string s2){
	int len1=s1.size(),len2=s2.size(),len=max(len1,len2);
	for(int i=1;i<=len;i++) a[i]=0;
	for(int i=1;i<=len1;i++) a[i]+=s1[len1-i]-'0';
	for(int i=1;i<=len2;i++) a[i]+=s2[len2-i]-'0';
	return chg(adjust1(len));
}
string operator -(string s1,string s2){
	int len1=s1.size(),len2=s2.size();
	for(int i=1;i<=len1;i++) a[i]=s1[len1-i]-'0';
	for(int i=1;i<=len2;i++) a[i]-=s2[len2-i]-'0';
	return chg(adjust2(len1));
}
string operator *(string s1,string s2){
	int len1=s1.size(),len2=s2.size();
	int len=len1+len2-1;
	for(int i=1;i<=len;i++) a[i]=0;
	for(int i=1;i<=len1;i++) 
		for(int j=1;j<=len2;j++)
			a[i+j-1]+=(s1[len1-i]-'0')*(s2[len2-j]-'0');
	return chg(adjust1(len));
}
string operator /(string s1,int x){
	string s2="";
	int r=0;
	for(int i=0;i<s1.size();i++){
		r=r*10+s1[i]-'0';
		s2+=r/x+'0';
		if(s2=="0") s2="";
		r%=x;
	}
	if(s2=="") s2="0";
	return s2;
}
int operator %(string s1,int x){
	int r=0;
	for(int i=0;i<s1.size();i++)
		r=(r*10+s1[i]-'0')%x;
	return r;
}
string operator +(string s1,int x){
	int len=s1.size();
	for(int i=1;i<=len;i++) a[i]=s1[len-i]-'0';
	a[1]+=x;
	return chg(adjust1(len));
}
string operator -(string s1,int x){
	int len=s1.size();
	for(int i=1;i<=len;i++) a[i]=s1[len-i]-'0';
	for(int i=1;x;i++,x/=10) a[i]-=x%10;
	return chg(adjust2(len));
}
string operator *(string s1,int x){
	int len=s1.size();
	for(int i=1;i<=len;i++) a[i]=(s1[len-i]-'0')*x;
	return chg(adjust1(len));
}
string change(int x){
	if(x==0) return "0";
	string s="";
	for(;x;x/=10) s=(char)(x%10+'0')+s;
	return s;
}
int main(){
	int x;
	string s1,s2,s3;
	cin>>s1>>s2>>x;
	cout<<change(x)<<endl;
	cout<<cmp(s1,s2)<<endl;
	cout<<s1+s2<<endl;
	cout<<s1-s2<<endl;
	cout<<s1*s2<<endl;
	cout<<"-------"<<endl;
	cout<<s1+x<<endl;
	cout<<s1-x<<endl;
	cout<<s1*x<<endl;
	cout<<s1/x<<endl;
	cout<<s1%x<<endl;
	return 0;
}
