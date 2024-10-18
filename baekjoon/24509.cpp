#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool compare1(vector<int> i, vector<int> j) {
    if (i[1] == j[1]) return i[0] < j[0];
    return i[1] > j[1];
}

bool compare2(vector<int> i, vector<int> j) {
    if (i[2] == j[2]) return i[0] < j[0];
    return i[2] > j[2];
}

bool compare3(vector<int> i, vector<int> j) {
    if (i[3] == j[3]) return i[0] < j[0];
    return i[3] > j[3];
}

bool compare4(vector<int> i, vector<int> j) {
    if (i[4] == j[4]) return i[0] < j[0];
    return i[4] > j[4];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<vector<int>> a(n, vector<int>(5));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 5; j++) {
            cin >> a[i][j];
        }
    }

    vector<bool> chk(n + 1, 0);

    sort(a.begin(), a.end(), compare1);
    for(int i = 0; i < n; i++) {
        if (!chk[a[i][0]]) {
            cout << a[i][0] << ' ';
            chk[a[i][0]] = true;
            break;
        }
    }

    sort(a.begin(), a.end(), compare2);
    for(int i = 0; i < n; i++) {
        if (!chk[a[i][0]]) {
            cout << a[i][0] << ' ';
            chk[a[i][0]] = true;
            break;
        }
    }

    sort(a.begin(), a.end(), compare3);
    for(int i = 0; i < n; i++) {
        if (!chk[a[i][0]]) {
            cout << a[i][0] << ' ';
            chk[a[i][0]] = true;
            break;
        }
    }

    sort(a.begin(), a.end(), compare4);
    for(int i = 0; i < n; i++) {
        if (!chk[a[i][0]]) {
            cout << a[i][0] << ' ';
            chk[a[i][0]] = true;
            break;
        }
    }

    cout << '\n';
}