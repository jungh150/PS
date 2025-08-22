#include <iostream>
using namespace std;

void solve() {
    int n;
    cin >> n;
    string s;
    getline(cin, s); // 버퍼에 남은 \n 없애기
    while (n--) {
        getline(cin, s);
        if (s == "Never gonna give you up" || s == "Never gonna let you down" || s == "Never gonna run around and desert you" || s == "Never gonna make you cry" || s == "Never gonna say goodbye" || s == "Never gonna tell a lie and hurt you" || s == "Never gonna stop") continue;
        cout << "Yes\n";
        return;
    }
    cout << "No\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}