#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        string a, b, c, d;
        cin >> a >> b >> c >> d;

        // 첫번째, 두번째 조건
        if (a[1] == b[1] && b[1] == c[1]) {
            if (a[0] == b[0] && b[0] == c[0]) {
                cout << ":)\n";
                continue;
            }
            vector<int> arr(3);
            arr[0] = a[0] - '0';
            arr[1] = b[0] - '0';
            arr[2] = c[0] - '0';
            sort(arr.begin(), arr.end());
            if (arr[0] + 1 == arr[1] && arr[1] + 1 == arr[2]) {
                cout << ":)\n";
                continue;
            }
        }
        if (a[1] == b[1] && b[1] == d[1]) {
            if (a[0] == b[0] && b[0] == d[0]) {
                cout << ":)\n";
                continue;
            }
            vector<int> arr(3);
            arr[0] = a[0] - '0';
            arr[1] = b[0] - '0';
            arr[2] = d[0] - '0';
            sort(arr.begin(), arr.end());
            if (arr[0] + 1 == arr[1] && arr[1] + 1 == arr[2]) {
                cout << ":)\n";
                continue;
            }
        }
        if (a[1] == c[1] && c[1] == d[1]) {
            if (a[0] == c[0] && c[0] == d[0]) {
                cout << ":)\n";
                continue;
            }
            vector<int> arr(3);
            arr[0] = a[0] - '0';
            arr[1] = c[0] - '0';
            arr[2] = d[0] - '0';
            sort(arr.begin(), arr.end());
            if (arr[0] + 1 == arr[1] && arr[1] + 1 == arr[2]) {
                cout << ":)\n";
                continue;
            }
        }
        if (b[1] == c[1] && c[1] == d[1]) {
            if (b[0] == c[0] && c[0] == d[0]) {
                cout << ":)\n";
                continue;
            }
            vector<int> arr(3);
            arr[0] = b[0] - '0';
            arr[1] = c[0] - '0';
            arr[2] = d[0] - '0';
            sort(arr.begin(), arr.end());
            if (arr[0] + 1 == arr[1] && arr[1] + 1 == arr[2]) {
                cout << ":)\n";
                continue;
            }
        }
        // 세번째 조건
        if ((a == b && c == d) || (a == c && b == d) || (a == d && b == c)) {
            cout << ":)\n";
            continue;
        }
        cout << ":(\n";
    }
}