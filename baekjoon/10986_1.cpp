#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    // n: 배열의 크기, m: 나누는 값
    int n, m;
    cin >> n >> m;

    // a: 입력 배열
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // cnt[i]: 나머지가 i인 누적합이 등장한 횟수
    vector<int> cnt(m, 0);
    cnt[0] = 1;  // 누적합이 처음부터 나머지 0인 경우 처리

    int tmp = 0;
    for (int i = 0; i < n; i++) {
        tmp = (tmp + a[i]) % m;
        cnt[tmp]++;  // cnt 배열 갱신
    }

    long long ans = 0;
    for (int i = 0; i < m; i++) {
        ans += ((1LL * cnt[i] * (cnt[i] - 1)) / 2);  // 같은 나머지를 가진 것들끼리 조합 계산
    }

    cout << ans << '\n';
}