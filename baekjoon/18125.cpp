#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int r, c;
    cin >> r >> c;

    vector<vector<int>> a(c, vector<int>(r));
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < r; j++) {
            cin >> a[i][j];
        }
    }

    vector<vector<int>> b(r, vector<int>(c));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> b[i][j];
        }
    }

    for (int i = 0; i < c; i++) {
        for (int j = 0; j < r; j++) {
            if (a[i][j] != b[j][c - i - 1]) {
                cout << "|>___/|     /}\n| O O |    / }\n( =0= )\"\"\"\"  \\\n| ^  ____    |\n|_|_/    ||__|\n";
                return 0;
            }
        }
    }

    cout << "|>___/|        /}\n| O < |       / }\n(==0==)------/ }\n| ^  _____    |\n|_|_/     ||__|\n";
}