#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    string s;
    cin >> n >> s;

    if (s[s.size() - 1] == 'A' || s[s.size() - 1] == 'B' || s[s.size() - 1] == 'C') s += '0';
    
    vector<string> bf;
    int sz = s.size();
    for (int i = 1; i < sz; i++) {
        if (s[i] == '+' || s[i] == '0' || s[i] == '-') {
            bf.push_back(string(1, s[i - 1]) + s[i]);
        } else {
            if (s[i - 1] == 'A' || s[i - 1] == 'B' || s[i - 1] == 'C') bf.push_back(string(1, s[i - 1]) + '0');
        }
    }

    for (int i = 0; i < n; i++) {
        if (bf[i] == "C+" || bf[i] == "C0" || bf[i] == "C-") {
            cout << "B";
        } else if (bf[i] == "B0" || bf[i] == "B-") {
            if (i == 0 || bf[i - 1] == "C+" || bf[i - 1] == "C0" || bf[i - 1] == "C-") cout << "D";
            else cout << "B";
        } else if (bf[i] == "A-" || bf[i] == "B+") {
            if (i == 0 || bf[i - 1] == "B0" || bf[i - 1] == "B-" || bf[i - 1] == "C+" || bf[i - 1] == "C0" || bf[i - 1] == "C-") cout << "P";
            else cout << "D";
        } else if (bf[i] == "A0") {
            if (i == 0 || bf[i - 1] == "A-" || bf[i - 1] == "B+" || bf[i - 1] == "B0" || bf[i - 1] == "B-" || bf[i - 1] == "C+" || bf[i - 1] == "C0" || bf[i - 1] == "C-") cout << "E";
            else cout << "P";
        } else if (bf[i] == "A+") {
            cout << "E";
        }
    }
    cout << '\n';
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