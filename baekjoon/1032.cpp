#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<string> data(n);
    string ans = "";
    for (int i = 0; i < n; i++) {
        cin >> data[i];
    }

    int len = data[0].size();
    for (int i = 0; i < len; i++) {
        bool isSame = true;
        for (int j = 1; j < n; j++) {
            if (data[0][i] != data[j][i]) {
                isSame = false;
                break;
            }
        }
        if (isSame) ans = ans + data[0][i];
        else ans = ans + '?';
    }

    cout << ans << '\n';
}