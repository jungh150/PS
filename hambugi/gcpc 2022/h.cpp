#include <iostream>
#include <vector>
using namespace std;

int sz = 1e4 + 1;

void solve () {
    vector<vector<vector<int>>> group(4, vector<vector<int>>(4));
    group[0][0] = {0, 1};
    group[0][1] = {2, 3};
    group[0][2] = {4, 5};
    group[0][3] = {6, -1};
    group[1][0] = {7, 8};
    group[1][1] = {9, 10};
    group[1][2] = {11, 12};
    group[1][3] = {13, -1};
    group[2][0] = {14, 15};
    group[2][1] = {16, 17};
    group[2][2] = {18, -1};
    group[2][3] = {19, -1};
    group[3][0] = {20, 21};
    group[3][1] = {22, 23};
    group[3][2] = {24, -1};
    group[3][3] = {25, -1};

    vector<vector<int>> ans(sz, vector<int>(3));

    // 1-1 query
    string s = "";
    for (int j = 0; j < 4; j++) {
        for (int k = 0; k < 2; k++) {
            if (group[0][j][k] != -1) s += ('a' + group[0][j][k]);
            if (group[1][j][k] != -1) s += ('a' + group[1][j][k]);
        }
    }
    cout << "? " << s << endl;

    int n;
    cin >> n;
    vector<bool> chk1(sz, false);
    
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        chk1[x] = true;
    }

    // 1-2 query
    s = "";
    for (int j = 0; j < 4; j++) {
        for (int k = 0; k < 2; k++) {
            if (group[1][j][k] != -1) s += ('a' + group[1][j][k]);
            if (group[2][j][k] != -1) s += ('a' + group[2][j][k]);
        }
    }
    cout << "? " << s << endl;

    cin >> n;
    vector<bool> chk2(sz, false);
    
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        chk2[x] = true;
    }

    // 처리
    for (int i = 1; i < sz; i++) {
        if (chk1[i] && !chk2[i]) ans[i][0] = 0;
        else if (chk1[i] && chk2[i]) ans[i][0] = 1;
        else if (!chk1[i] && chk2[i]) ans[i][0] = 2;
        else if (!chk1[i] && !chk2[i]) ans[i][0] = 3;
    }

    // 2-1 query
    s = "";
    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < 2; k++) {
            if (group[i][0][k] != -1) s += ('a' + group[i][0][k]);
            if (group[i][1][k] != -1) s += ('a' + group[i][1][k]);
        }
    }
    cout << "? " << s << endl;

    cin >> n;
    chk1 = vector<bool>(sz, false);
    
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        chk1[x] = true;
    }

    // 2-2 query
    s = "";
    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < 2; k++) {
            if (group[i][1][k] != -1) s += ('a' + group[i][1][k]);
            if (group[i][2][k] != -1) s += ('a' + group[i][2][k]);
        }
    }
    cout << "? " << s << endl;

    cin >> n;
    chk2 = vector<bool>(sz, false);
    
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        chk2[x] = true;
    }

    // 처리
    for (int i = 1; i < sz; i++) {
        if (chk1[i] && !chk2[i]) ans[i][1] = 0;
        else if (chk1[i] && chk2[i]) ans[i][1] = 1;
        else if (!chk1[i] && chk2[i]) ans[i][1] = 2;
        else if (!chk1[i] && !chk2[i]) ans[i][1] = 3;
    }

    // 3-1 query
    s = "";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (group[i][j][0] != -1) s += ('a' + group[i][j][0]);
        }
    }
    cout << "? " << s << endl;

    cin >> n;
    chk1 = vector<bool>(sz, false);
    
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        chk1[x] = true;
    }

    // 3-2 query
    s = "";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (group[i][j][1] != -1) s += ('a' + group[i][j][1]);
        }
    }
    cout << "? " << s << endl;

    cin >> n;
    chk2 = vector<bool>(sz, false);
    
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        chk2[x] = true;
    }

    // 처리
    for (int i = 1; i < sz; i++) {
        if (chk1[i]) ans[i][2] = 0;
        else if (chk2[i]) ans[i][2] = 1;
        else ans[i][2] = -1;
    }

    string ansstr = "";
    for (int i = 1; i < sz; i++) {
        if (ans[i][2] == -1) break;
        ansstr += ('a' + group[ans[i][0]][ans[i][1]][ans[i][2]]);
    }
    cout << "! " << ansstr << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    // cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}