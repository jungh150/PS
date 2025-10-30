#include <iostream>
using namespace std;

bool compare(string s) {
    if (s.size() > 19) return true;
    else if (s.size() < 19) return false;
    else return s > "9223372036854775807";
}

void solve() {
    string s1, s2;
    long long r;
    cin >> s1 >> s2 >> r;

    if (s1 == "0" || s2 == "0") {
        cout << "0\n";
        return;
    }

    if (compare(s1) > 0 || compare(s2) > 0) {
        cout << "overflow\n";
        return;
    }

    long long a = stoll(s1);
    long long b = stoll(s2);

    if (a > (r / b)) cout << "overflow\n";
    else cout << a * b << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}