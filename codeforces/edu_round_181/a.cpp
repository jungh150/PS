#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        string s;
        cin >> s;

        vector<int> a(26, 0);
        for (char c: s) a[c - 'A']++;

        for (int i = 0; i < a['T' - 'A']; i++) cout << 'T';
        for (int i = 0; i < a['F' - 'A']; i++) cout << 'F';
        for (int i = 0; i < a['N' - 'A']; i++) cout << 'N';

        for (int i = 0; i < 26; i++) {
            if (i == 'T' - 'A' || i == 'F' - 'A' || i == 'N' - 'A') continue;
            for (int j = 0; j < a[i]; j++) cout << (char) (i + 'A');
        }
        cout << '\n';
    }
}