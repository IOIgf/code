#include <bits/stdc++.h>
#define int long long
using namespace std;
int ans = 0;
int n, S;
void dfs(int pos, int sum, vector<int>& cur) {
	if (pos == n) {
		if (sum == S) {
			int x = 2 * cur[0];
			for (int i=1;i<n;i++) {
				x = (x+cur[i])-(x^cur[i]);
			}
			ans = (ans + x) % 599999;
		}
		return;
	}
	for (int v=0;v<=S-sum;v++) {
		cur.push_back(v);
		dfs(pos + 1, sum + v, cur);
		cur.pop_back();
	}
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int Q;
	cin >> Q;
	while (Q--) {
		cin >> n >> S;
		if (n > 10 || S > 1000) {
			cout << "0\n";
			continue;
		}
		ans = 0;
		vector<int> cur;
		dfs(0, 0, cur);
		cout << ans % 599999 << '\n';
	}
	return 0;
}
