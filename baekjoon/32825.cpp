#include <iostream>
#include <vector>
using namespace std;

int A, B, C, D, E, F, G, H;
vector<int> num; // 그 알파벳에 들어가는 수가 몇인지
vector<bool> chk; // 숫자를 사용했는지
int ans = 0;

bool promising() {
    if (num[1] != 0 && num[5] != 0 && num[9] != 0 && num[12] != 0) {
        if ((num[1] + num[5] + num[9] + num[12]) != A) return false;
    }
    if (num[2] != 0 && num[6] != 0 && num[10] != 0 && num[13] != 0) {
        if ((num[2] + num[6] + num[10] + num[13]) != B) return false;
    }
    if (num[3] != 0 && num[7] != 0 && num[11] != 0) {
        if ((num[3] + num[7] + num[11]) != C) return false;
    }
    if (num[4] != 0 && num[8] != 0) {
        if ((num[4] + num[8]) != D) return false;
    }
    if (num[1] != 0 && num[2] != 0 && num[3] != 0 && num[4] != 0) {
        if ((num[1] + num[2] + num[3] + num[4]) != E) return false;
    }
    if (num[5] != 0 && num[6] != 0 && num[7] != 0 && num[8] != 0) {
        if ((num[5] + num[6] + num[7] + num[8]) != F) return false;
    }
    if (num[9] != 0 && num[10] != 0 && num[11] != 0) {
        if ((num[9] + num[10] + num[11]) != G) return false;
    }
    if (num[12] != 0 && num[13] != 0) {
        if ((num[12] + num[13]) != H) return false;
    }
    return true;
}

void bt(int cur) {
    if (cur == 14) {
        if (promising()) ans++;
        return;
    }
    if (num[cur] != 0) {
        bt(cur + 1);
        return;
    }
    for (int i = 1; i < 14; i++) {
        if (!chk[i]) {
            chk[i] = true;
            num[cur] = i;
            if (promising()) bt(cur + 1);
            chk[i] = false;
            num[cur] = 0;
        }
    }
}

void solve() {
    cin >> A >> B >> C >> D >> E >> F >> G >> H;

    for (int i = 1; i < 14; i++) {
        for (int j = 1; j < 14; j++) {
            if (i == j) continue;
            num = vector<int>(14, 0);
            chk = vector<bool>(14, false);
            num[4] = i; // d
            num[8] = D - i; // h
            num[12] = j; // l
            num[13] = H - j; // m
            // h, m 범위 체크
            if (num[8] < 1 || num[8] > 13 || num[13] < 1 || num[13] > 13) continue;
            // 동일한 거 있는지 체크
            if (num[4] == num[8] || num[4] == num[13] || num[12] == num[13] || num[12] == num[8]) continue;
            chk[num[4]] = true;
            chk[num[8]] = true;
            chk[num[12]] = true;
            chk[num[13]] = true;
            bt(1);
        }
    }

    cout << ans << '\n';
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