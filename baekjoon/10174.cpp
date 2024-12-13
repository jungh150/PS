#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tn;
    cin >> tn;
    cin.ignore(); // 남아있는 개행 문자를 제거

    while (tn--) {
        string s;
        getline(cin, s);
        int n = s.length();

        for (int i = 0; i < n; i++) {
            if (s[i] >= 'A' && s[i] <= 'Z') s[i] -= ('A' - 'a');
        }

        bool isp = true;
        for (int i = 0; i < n / 2; i++) {
            if (s[i] != s[n - i - 1]) isp = false;
        }

        if (isp) cout << "Yes\n";
        else cout << "No\n";
    }
}