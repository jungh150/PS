#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<vector<int>> m(n, vector<int>(n));
    vector<int> chk(n * n + 1, false);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            m[i][j] = x;
            chk[x] = true;
        }
    }

    for (int i = 1; i < n * n + 1; i++) {
        if (!chk[i]) {
            cout << "FALSE\n";
            return 0;
        }
    }

    int correctsum = (n * (n * n + 1)) / 2;
    for (int i = 0; i < n; i++) {
        int rowsum = 0;
        int colsum = 0;
        for (int j = 0; j < n; j++) {
            rowsum += m[i][j];
            colsum += m[j][i];
        }
        if (rowsum != correctsum || colsum != correctsum) {
            cout << "FALSE\n";
            return 0;
        }
    }

    int diagsum = 0;
    for (int i = 0; i < n; i++) {
        diagsum += m[i][i];
    }
    if (diagsum != correctsum) {
        cout << "FALSE\n";
        return 0;
    }

    diagsum = 0;
    for (int i = 0; i < n; i++) {
        diagsum += m[i][n - i - 1];
    }
    if (diagsum != correctsum) {
        cout << "FALSE\n";
        return 0;
    }

    cout << "TRUE\n";
}