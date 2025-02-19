#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;
    int n = s.size();

    int y = n;
    int k = n;
    string yonsei = "YONSEI";
    string korea = "KOREA";

    int yt = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == yonsei[yt]) {
            yt++;
        }
        if (yt == 6) {
            y = i;
            break;
        }
    }

    int kt = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == korea[kt]) {
            kt++;
        }
        if (kt == 5) {
            k = i;
            break;
        }
    }

    if (y < k) cout << yonsei << '\n';
    else cout << korea << '\n';
}