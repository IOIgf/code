/**
 * Manacher（马拉车）算法模板
 * 功能：在 O(n) 时间内求解字符串的所有回文子串信息
 * 适用：最长回文子串、回文子串计数等
 *
 * 使用说明：
 *   1. 调用 manacher(s) 得到半径数组 d
 *   2. 原串下标 i 处：
 *      - 奇回文半径 d1[i]（包含中心，即 d1[i] = 实际半径 + 1）
 *      - 偶回文半径 d2[i]（d2[i] = 以 i 与 i-1 为中心的回文半径）
 *   3. 最长回文子串长度 = max(2*d1[i]-1, 2*d2[i])
 */
#include <bits/stdc++.h>
using namespace std;

// 方法一：求 d1（奇回文半径）和 d2（偶回文半径）
// d1[i]：以 i 为中心的最长奇回文半径（含中心），即长度 = 2*d1[i] - 1
// d2[i]：以 i-1, i 为中心的最长偶回文半径，即长度 = 2*d2[i]
struct Manacher {
    vector<int> d1, d2; // 注意 d2 下标从 1 开始有意义（d2[0]=0）

    void run(const string& s) {
        int n = (int)s.size();
        d1.assign(n, 0);
        d2.assign(n, 0);

        // ---------- 奇回文 ----------
        for (int i = 0, l = 0, r = -1; i < n; i++) {
            int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
            while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) k++;
            d1[i] = k--;
            if (i + k > r) { l = i - k; r = i + k; }
        }

        // ---------- 偶回文 ----------
        for (int i = 0, l = 0, r = -1; i < n; i++) {
            int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
            while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) k++;
            d2[i] = k--;
            if (i + k > r) { l = i - k - 1; r = i + k; }
        }
    }

    // 最长回文子串长度
    int longestLength(const string& s) {
        run(s);
        int ans = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            ans = max(ans, 2 * d1[i] - 1); // 奇回文
            ans = max(ans, 2 * d2[i]);     // 偶回文
        }
        return ans;
    }

    // 最长回文子串本体
    string longestSubstring(const string& s) {
        run(s);
        int n = (int)s.size();
        int bestLen = 0, bestL = 0;
        for (int i = 0; i < n; i++) {
            if (2 * d1[i] - 1 > bestLen) { bestLen = 2 * d1[i] - 1; bestL = i - d1[i] + 1; }
            if (2 * d2[i] > bestLen)     { bestLen = 2 * d2[i];     bestL = i - d2[i];     }
        }
        return s.substr(bestL, bestLen);
    }

    // 回文子串总数
    long long countPalindromes(const string& s) {
        run(s);
        long long cnt = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            cnt += d1[i];  // 奇回文个数
            cnt += d2[i];  // 偶回文个数
        }
        return cnt;
    }
};

// 方法二：插入分隔符的统一写法（可选，另一种风格）
// 将原串变为 #a#b#c#，所有回文统一按奇数处理，半径数组 p
vector<int> manacher_unified(const string& s) {
    string t = "#";
    for (char c : s) { t += c; t += '#'; }
    int n = (int)t.size();
    vector<int> p(n, 0);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(p[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && t[i - k] == t[i + k]) k++;
        p[i] = k--;
        if (i + k > r) { l = i - k; r = i + k; }
    }
    return p;
    // 原串最长回文长度 = max(p[i]) - 1
}

// 简单自测
void test() {
    vector<string> cases = {
        "babad",
        "cbbd",
        "abcba",
        "a",
        "abacdfgdcaba",
        "aaaa"
    };
    Manacher m;
    for (auto& s : cases) {
        cout << "s = " << s << "\n";
        cout << "  最长回文子串: " << m.longestSubstring(s) << "\n";
        cout << "  最长回文长度: " << m.longestLength(s) << "\n";
        cout << "  回文总数: " << m.countPalindromes(s) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    test();

    // 用户输入模式：每行一个字符串，Ctrl+Z (Windows) / Ctrl+D (Linux) 结束
    // string s;
    // while (cin >> s) {
    //     Manacher m;
    //     cout << "最长回文子串: " << m.longestSubstring(s) << "\n";
    // }
    return 0;
}
