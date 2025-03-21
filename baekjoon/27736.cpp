#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    int a = 0; // 찬성
    int b = 0; // 반대
    int c = 0; // 기권

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x == 1) a++;
        else if (x == -1) b++;
        else if (x == 0) c++;
    }

    int half = (n + 1) / 2;

    if (c >= half) {
        cout << "INVALID\n";
    } else {
        if (b >= a) cout << "REJECTED\n";
        else cout << "APPROVED\n";
    }
}