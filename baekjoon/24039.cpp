#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    // pn: 배열 p의 크기
    int pn = 110;
    // p: 소수 판별을 위한 배열 (기본값은 true)
    vector<bool> p(pn, true);
    p[0] = p[1] = false; // 0과 1은 소수가 아님

    // 에라토스테네스의 체
    int tmp = sqrt(n);
    for (int i = 2; i <= tmp; i++) {
        if (p[i]) { // i가 소수라면
            for (int j = i + i; j <= n; j += i) p[j] = false;
        }
    }

    int pre = 2; // 이전 소수
    int cur; // 현재 소수
    for (int i = 3; i < pn; i++) {
        if (!p[i]) continue; // 소수가 아니라면 건너뛰기
        cur = i;
        int mul = pre * cur; // 이전 소수와 현재 소수의 곱 = 특별한 수
        if (mul > n) { // 특별한 수가 n보다 크면 출력
            cout << mul << '\n';
            return 0;
        } else { // 작으면 계속 반복
            pre = cur;
        }
    }
}