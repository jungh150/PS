#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    vector<vector<int>> a(k + 1);
    string tmp = "";

    for (char c: s) {
        if (c == ',') {
            a[0].push_back(stoi(tmp));
            tmp = "";
        } else {
            tmp += c;
        }
    }
    a[0].push_back(stoi(tmp));

    for (int i = 1; i < k + 1; i++) {
        for (int j = 1; j < n - i + 1; j++) {
            a[i].push_back(a[i - 1][j] - a[i - 1][j - 1]);
        }
    }

    for (int i = 0; i < n - k; i++) {
        cout << a[k][i];
        if (i != n - k - 1) cout << ',';
        else cout << '\n';
    }
}