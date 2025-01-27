#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int m, n;
    cin >> m >> n;

    // 소수 판별을 위한 배열 생성 (기본값은 true)
    vector<bool> p(n + 1, true);
    p[0] = p[1] = false; // 0과 1은 소수가 아님
    int tmp = sqrt(n);

    // 에라토스테네스의 체
    for (int i = 2; i <= tmp; i++) {
        if (p[i]) { // i가 소수라면
            for (int j = i + i; j <= n; j += i) p[j] = false;
        }
    }

    for (int i = m; i <= n; i++) {
        if (p[i]) cout << i << '\n';
    }

    return 0;
}