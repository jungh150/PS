#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<string> img1(n);
    vector<string> img2(n);

    for (int i = 0; i < n; i++) cin >> img1[i];
    for (int i = 0; i < n; i++) cin >> img2[i];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (img1[i][j] != img2[i][2 * j]) {
                cout << "Not Eyfa\n";
                return 0;
            }
            if (img1[i][j] != img2[i][2 * j + 1]) {
                cout << "Not Eyfa\n";
                return 0;
            }
        }
    }

    cout << "Eyfa\n";
}