#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int a, b, c;
    cin >> a >> b >> c;

    // b가 0인 경우
    if (b == 0) {
        for (int x = 1; x <= 10; x++) {
            if (a * x == c) cout << "1 2 3 4 5 6 7 8 9 10\n";  // 방정식이 성립하면 모든 y 값 출력
            else cout << "0\n";
        }
        return 0;
    }

    // b가 0이 아닌 경우
    for (int x = 1; x <= 10; x++) {
        int tmp = c - a * x;
        if (tmp % b == 0) {  // y가 정수인지 판별
            int y = tmp / b;
            if (y >= 1 && y <= 10) cout << y << '\n';  // y가 1~10 사이에 있으면 출력
            else cout << "0\n";
        } else cout << "0\n";
    }
}