#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    // 색을 저장하는 배열 생성 (기본값은 0)
    vector<int> p(n + 1, 0);
    p[1] = 1;

    // 에라토스테네스의 체를 활용하여 색칠하기
    int color = 2;
    for (int i = 2; i < n + 1; i++) {
        if (p[i] == 0) { // i가 소수라면
            for (int j = i; j <= n; j += i) {
                p[j] = color;
            }
            color++;
        }
    }

    cout << color - 1 << '\n';
    for (int i = 1; i < n + 1; i++) cout << p[i] << ' ';
    cout << '\n';
}