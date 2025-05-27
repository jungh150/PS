#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<char>> ans(m, vector<char>(n));

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            if (s[j] == '.' || s[j] == 'O') ans[m - j - 1][i] = s[j];
            else if (s[j] == '-') ans[m - j - 1][i] = '|';
            else if (s[j] == '|') ans[m - j - 1][i] = '-';
            else if (s[j] == '\\') ans[m - j - 1][i] = '/';
            else if (s[j] == '/') ans[m - j - 1][i] = '\\';
            else if (s[j] == '^') ans[m - j - 1][i] = '<';
            else if (s[j] == '<') ans[m - j - 1][i] = 'v';
            else if (s[j] == 'v') ans[m - j - 1][i] = '>';
            else if (s[j] == '>') ans[m - j - 1][i] = '^';
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << ans[i][j];
        }
        cout << '\n';
    }
}