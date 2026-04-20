#include <iostream>
#include <set>
using namespace std;

void solve() {
    string s;
    getline(cin, s);

    set<string> a;
    while (1) {
        string tmp;
        getline(cin, tmp);

        if (tmp == "what does the fox say?") break;

        int n = tmp.size();
        for (int i = 0; i < n; i++) {
            if (tmp.substr(i, 4) == "goes") {
                a.insert(tmp.substr(i + 5));
            }
        }
    }

    s += ' ';
    int sz = s.size();
    string word = "";
    for (int i = 0; i < sz; i++) {
        if (s[i] == ' ') {
            if (!a.count(word)) cout << word << ' ';
            word = "";
        } else {
            word += s[i];
        }
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    cin >> T;
    cin.ignore();
    for (int i = 0; i < T; i++) {
        solve();
    }
}