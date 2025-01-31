#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// 구해야 하는 소수의 최대 크기
// (a, b의 최댓값의 제곱근보다 크면 됨)
int const MAX_SIZE = 2000000;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    // p: 소수 판별을 위한 배열 (기본값은 true) <- 시간을 줄이기 위해
    vector<bool> p(MAX_SIZE, true);
    p[0] = p[1] = false; // 0과 1은 소수가 아님
    // prime: 소수를 넣는 배열
    vector<int> prime;

    // 에라토스테네스의 체
    int tmp = sqrt(MAX_SIZE);
    for (int i = 2; i <= tmp; i++) {
        if (p[i]) { // i가 소수라면
            for (int j = i + i; j < MAX_SIZE; j += i) p[j] = false;
        }
    }

    // 소수를 미리 배열에 담아두기 <- 시간을 줄이기 위해
    for (int i = 1; i < MAX_SIZE; i++) {
        if (p[i]) prime.push_back(i);
    }

    while (t--) {
        long long a, b;
        cin >> a >> b;

        if (a + b <= 3) { // 2와 3 예외 처리 주의!
            cout << "NO\n";
        } else if ((a + b) % 2 == 0) { // 짝수면 무조건 YES
            cout << "YES\n";
        } else { // 홀수면 2를 뺀 값이 소수인지 체크
            bool ans = true;
            for (int i: prime) {
                if (a + b - 2 == i) { // 앞에서 구한 소수면 YES
                    break;
                }
                if ((a + b - 2) % i == 0) { // 앞에서 구한 소수로 나누어 떨어지면 NO
                    ans = false;
                    break;
                }
            }
            
            if (ans) cout << "YES\n";
            else cout << "NO\n";
        }
    }
}