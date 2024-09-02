#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    string str;
    cin >> n >> m >> str;

    int cnt = 0;
    for (int i = 0; i < m; i++) {
        int tmp = 0;
        if (str[i] == 'O') continue;
        while (str[i + 1] == 'O' && str[i + 2] == 'I') {
            tmp++;
            if (tmp == n) {
                cnt++;
                tmp--;
            }
            i += 2;
        }
    }

    cout << cnt << '\n';
}