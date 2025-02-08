#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    
    vector<string> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int ans = 1; // 정사각형 변의 길이의 최대

    // 모든 좌표 (si, sj)를 정사각형의 왼쪽 상단 점으로 설정
    for (int si = 0; si < n; si++) {
        for (int sj = 0; sj < m; sj++) {
            // 가능한 정사각형 크기 탐색
            for (int size = 1; si + size < n && sj + size < m; size++) {
                if (a[si][sj] == a[si][sj + size] && 
                    a[si][sj] == a[si + size][sj] && 
                    a[si][sj] == a[si + size][sj + size]) {
                    ans = max(ans, size + 1);
                }
            }
        }
    }

    // 제곱한 후 출력
    cout << ans * ans << '\n';
}