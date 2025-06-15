#include <iostream>
#include <vector>
using namespace std;

int n, s, r, cn;
int ans = 100;
vector<int> a;
vector<bool> b;
vector<int> c;

void bt(int idx, int cnt) {
    if (idx == s) {
        ans = min(ans, cnt);
        return;
    }
    // 전 팀한테 빌리기
    if (c[idx] > 1 && b[c[idx] - 1]) {
        b[c[idx] - 1] = false;
        bt(idx + 1, cnt - 1);
        b[c[idx] - 1] = true;
    }
    // 다음 팀한테 빌리기
    if (c[idx] < n && b[c[idx] + 1]) {
        b[c[idx] + 1] = false;
        bt(idx + 1, cnt - 1);
        b[c[idx] + 1] = true;
    }
    // 안 빌리기
    bt(idx + 1, cnt);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> s >> r;

    a = vector<int>(s);
    b = vector<bool>(n + 1, false);

    for (int i = 0; i < s; i++) cin >> a[i];
    for (int i = 0; i < r; i++) {
        int x;
        cin >> x;
        b[x] = true;
    }

    for (int x: a) {
        if (b[x]) {
            s--;
            b[x] = false;
        } else {
            c.push_back(x);
        }
    }
    cn = c.size();

    bt(0, s);

    cout << ans << '\n';
}