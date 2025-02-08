#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;

    // -999부터 999까지 가능한 x, y 값을 전부 탐색
    for (int x = -999; x < 1000; x++) {
        for (int y = -999; y < 1000; y++) {
            // 두 식을 모두 만족하는 (x, y) 값을 찾으면 출력 후 종료
            if ((a * x + b * y == c) && (d * x + e * y == f)) {
                cout << x << ' ' << y << '\n';
                break;
            }
        }
    }
}