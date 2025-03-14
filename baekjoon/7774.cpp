#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> mul1(n);
    vector<int> mul2(m);

    for (int i = 0; i < n; i++) cin >> mul1[i]; // a 플러그 -> b 콘센트
    for (int i = 0; i < m; i++) cin >> mul2[i]; // b 플러그 -> a 콘센트

    sort(mul1.begin(), mul1.end());
    sort(mul2.begin(), mul2.end());

    int acnt = 1;
    int bcnt = 0;
    int idx1 = n - 1;
    int idx2 = m - 1;

    while (idx2 >= 0) {
        // mul1 (b 콘센트를 여러개 갖는 멀티탭) 하나 꽂기
        if (idx1 >= 0) {
            acnt--;
            bcnt += mul1[idx1];
            idx1--;
        } else {
            break;
        }
        // mul2 (a 콘센트를 여러개 갖는 멀티탭) 꽂을 수 있는 만큼 꽂기
        while (bcnt > 0 && idx2 >= 0) {
            bcnt--;
            acnt += mul2[idx2];
            idx2--;
        }
    }

    cout << acnt << '\n';
}