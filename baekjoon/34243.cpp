#include <iostream>
#include <vector>
using namespace std;

void solve() {
    string s;
    cin >> s;
    int n = s.size();

    vector<int> ps(n + 1, 0); // 흥미도 prefix sum
    for (int i = 3; i < n + 1; i++) {
        ps[i] = ps[i - 1];
        if (s.substr(i - 3, 3) == "+^+") ps[i]++;
        else if (s.substr(i - 3, 3) == "-^-") ps[i]--;
    }

    vector<int> diff(n + 1, 0); // 특정 인덱스 삭제 시 흥미도 변화량

    for (int i = 3; i <= n - 2; i++) { // s에서 인덱스는 i - 1
        // 기존 점수 빼기
        if (s.substr(i - 3, 3) == "+^+") diff[i]--;
        else if (s.substr(i - 3, 3) == "-^-") diff[i]++;

        if (s.substr(i - 2, 3) == "+^+") diff[i]--;
        else if (s.substr(i - 2, 3) == "-^-") diff[i]++;

        if (s.substr(i - 1, 3) == "+^+") diff[i]--;
        else if (s.substr(i - 1, 3) == "-^-") diff[i]++;

        // 새로운 점수 더하기
        if (s.substr(i - 3, 2) + s[i] == "+^+") diff[i]++;
        else if (s.substr(i - 3, 2) + s[i] == "-^-") diff[i]--;

        if (s[i - 2] + s.substr(i, 2) == "+^+") diff[i]++;
        else if (s[i - 2] + s.substr(i, 2) == "-^-") diff[i]--;
    }

    // for (int x: ps) cout << x << ' ';
    // cout << '\n';
    // for (int x: diff) cout << x << ' ';
    // cout << '\n';

    vector<int> lg(n + 1);
    lg[1] = 0;
    for (int i = 2; i <= n; i++) lg[i] = lg[i/2] + 1;

    // sp[i][j]: i부터 시작해서 길이가 2^j인 구간의 diff 최댓값
    vector<vector<int>> sp(n + 1, vector<int>(20));
    for (int i = 1; i < n + 1; i++) sp[i][0] = diff[i];

    for (int j = 1; j < 20; j++) {
        for (int i = 1; i < n + 1; i++) {
            if (i + (1 << j) - 1 > n) break;
            sp[i][j] = max(sp[i][j - 1], sp[i + (1 << (j - 1))][j - 1]);
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;

        int score = ps[r] - ps[l + 1];

        if (r - l + 1 <= 2) {
            cout << 0 << '\n';
            continue;
        } else if (r - l + 1 == 3) {
            cout << max(0, score) << '\n';
            continue;
        }

        int diffmax = 0;
        int len = (r - 2) - (l + 2) + 1;
        if (len > 0) {
            int k = lg[len];
            diffmax = max(sp[l + 2][k], sp[(r - 2) - (1 << k) + 1][k]);
        }
        
        // l 삭제
        int tmp = 0;
        if (s.substr(l - 1, 3) == "+^+") tmp--;
        else if (s.substr(l - 1, 3) == "-^-") tmp++;
        diffmax = max(diffmax, tmp);

        // l + 1 삭제
        tmp = 0;
        if (s.substr(l - 1, 3) == "+^+") tmp--;
        else if (s.substr(l - 1, 3) == "-^-") tmp++;
        if (s.substr(l, 3) == "+^+") tmp--;
        else if (s.substr(l, 3) == "-^-") tmp++;
        if (s[l - 1] + s.substr(l + 1, 2) == "+^+") tmp++;
        else if (s[l - 1] + s.substr(l + 1, 2) == "-^-") tmp--;
        diffmax = max(diffmax, tmp);

        // r - 1 삭제
        tmp = 0;
        if (s.substr(r - 4, 3) == "+^+") tmp--;
        else if (s.substr(r - 4, 3) == "-^-") tmp++;
        if (s.substr(r - 3, 3) == "+^+") tmp--;
        else if (s.substr(r - 3, 3) == "-^-") tmp++;
        if (s.substr(r - 4, 2) + s[r - 1] == "+^+") tmp++;
        else if (s.substr(r - 4, 2) + s[r - 1] == "-^-") tmp--;
        diffmax = max(diffmax, tmp);

        // r 삭제
        tmp = 0;
        if (s.substr(r - 3, 3) == "+^+") tmp--;
        else if (s.substr(r - 3, 3) == "-^-") tmp++;
        diffmax = max(diffmax, tmp);

        cout << score + max(0, diffmax) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}