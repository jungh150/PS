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
    long long ans = 0;  // 정수 범위 초과 방지를 위해 long long 사용

    for (int i = 0; i < n; i++) {
        tmp = (tmp + a[i]) % m;
        ans += cnt[tmp];  // 현재 나머지가 같은 개수만큼 정답에 추가
        cnt[tmp]++;       // cnt 배열 갱신
    }

    cout << ans << '\n';
}