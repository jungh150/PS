#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    long long s = 1, e = 1e12 + 1;  // 최소, 최대 시간 설정
    long long ans = e;

    while (s <= e) {
        long long mid = (s + e) / 2;
        long long tmp = 0;

        // mid 시간 동안 터뜨릴 수 있는 풍선 개수 계산
        for (int x: a) {
            tmp += mid / x;
            if (tmp >= m) break;  // m개 이상이면 더 계산할 필요 없음
        }

        if (tmp < m) {  // 풍선을 충분히 못 터뜨렸다면 시간 증가
            s = mid + 1;
        } else {  // 충분히 터뜨릴 수 있다면 정답 후보로 저장하고 더 작은 값 탐색
            ans = mid;
            e = mid - 1;
        }
    }

    cout << ans << '\n';
    return 0;
}