#include <bits/stdc++.h>
using namespace std;
struct mat {
  int a[2][2];
  mat() {
    a[0][0] = a[1][1] = 0;
    a[1][0] = a[0][1] = 0x3f3f3f3f;
  }
  mat(int x, int y, int z, int w) {
    a[0][0] = x, a[0][1] = y, a[1][0] = z, a[1][1] = w;
  }
};
mat mul(const mat& x, const mat& y) {
  return {min(x.a[0][0] + y.a[0][0], x.a[0][1] + y.a[1][0]),
          min(x.a[0][0] + y.a[0][1], x.a[0][1] + y.a[1][1]),
          min(x.a[1][0] + y.a[0][0], x.a[1][1] + y.a[1][0]),
          min(x.a[1][0] + y.a[0][1], x.a[1][1] + y.a[1][1])};
}
struct random {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  uint64_t rnd() {
    sd ^= sd << 13, sd ^= sd >> 7;
    return sd ^= sd << 17;
  }
  void init() { cin >> sd >> b, sd = splitmix64(sd); }
  void genmat(mat& res) {
    uint64_t val = rnd();
    for (int i : {0, 1})
      for (int j : {0, 1}) res.a[i][j] = val >> ((i << 1 | j) << 4) & 0xff;
  }
  void genqry(int& l, int& r, int n) {
    if ((rnd() & 1) && b) {
      int c = rnd() % (n - b);
      l = rnd() % (n - c) + 1, r = l + c;
    } else {
      l = rnd() % n + 1, r = rnd() % n + 1;
      if (l > r) swap(l, r);
    }
  }
  uint64_t sd;
  int b;
} rnd;
struct output {
  int ans, kv[2][2];
  void init() {
    for (int i : {0, 1})
      for (int j : {0, 1}) cin >> kv[i][j];
  }
  void setres(mat res) {
    int tmp = 0;
    for (int i : {0, 1})
      for (int j : {0, 1}) tmp += res.a[i][j] ^ kv[i][j];
    ans ^= tmp;
  }
} out;
constexpr int N=(1<<20)+5;
int n, m, ans;
mat a[N],val[21][N];
int lg[N];
mat query(int l,int r){
	if(l==r) return a[l];
	int h=lg[(l-1)^(r-1)];
	return mul(val[h][l],val[h][r]);
}
signed main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> m, rnd.init(), out.init();
	for (int i = 1; i <= n; ++i) rnd.genmat(a[i]);
	int M=1;
	while(M<n) M<<=1;
	for(int i=1;i<M/2;i++) lg[i*2]=lg[i*2+1]=lg[i]+1;
	for(int i=n+1;i<=M;i++) a[i]=mat();
	for(int i=1;i<=M;i++) val[0][i]=a[i];
	for(int j=1;(1<<j)<M;j++){
		for(int i=1;i<=M;i++) val[j][i]=a[i];
		for(int k=1;k*(1<<j)<=M;k++){
			int l=(k-1)*(1<<j)+1,r=k*(1<<j);
			if(k%2){
				for(int i=r-1;i>=l;i--) 
					val[j][i]=mul(val[j][i],val[j][i+1]);
			}else{
				for(int i=l+1;i<=r;i++) 
					val[j][i]=mul(val[j][i-1],val[j][i]);
			}
		}
	}
	for (int l, r; m; --m) {
		rnd.genqry(l, r, n);
		mat ans=query(l,r);
		out.setres(ans);
	}
	return cout << out.ans << endl, 0;
}


